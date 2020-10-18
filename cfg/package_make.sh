#!/usr/bin/env bash

set -e

INTERNAL_OPTS=""
TYPE=""
DRY_RUN=""
CMAKE_OPTS=""
BUILD_ROOT="${PWD}/_build"
TEST_ONLY=""
TEST_OPTION="ENABLE_TEST"

function usage() {
  echo ""
  echo ""
  echo "./package_make.sh"
  echo -e "    -h, --help       |  This help"
  echo -e "    -t, --type       |  Choose what package to build: archive or native OS package"
  echo -e "    --dry-run        |  Only echo commands without real building"
  echo -e "    --test           |  Build and run only test configuration"
  echo -e "    -o, --options    |  Add string with additional cmake configure options. Example: -o \"-DVAR=1 -DVAR2=2\""
  echo -e "    -b, --buildroot  |  Path where to build project. Default: ${BUILD_ROOT}"
  echo ""
}

PARAMS=""
while (("$#")); do
  case "$1" in
  -h | --help)
    usage
    exit 0
    ;;
  --dry-run)
    DRY_RUN=1
    shift
    ;;
  --test)
    if [ -n "$2" ]; then
      TEST_ONLY=1
      TEST_OPTION="$2"
      shift 2
    else
      TEST_ONLY=1
      shift
    fi
    ;;
  -t | --type)
    if [ -n "$2" ] && [ ${2:0:1} != "-" ]; then
      TYPE=$2
      shift 2
    else
      echo "Error: Argument for $1 is missing" >&2
      exit 1
    fi
    ;;
  -b | --buildroot)
    if [ -n "$2" ] && [ ${2:0:1} != "-" ]; then
      BUILD_ROOT=$2
      shift 2
    else
      echo "Error: Argument for $1 is missing" >&2
      exit 1
    fi
    ;;
  -o | --options)
    if [ -n "$2" ] && [ ${2:0:1} != "-" ]; then
      CMAKE_OPTS=$2
      shift 2
    else
      echo "Error: Argument for $1 is missing" >&2
      exit 1
    fi
    ;;
  -* | --*=) # unsupported flags
    echo "Error: Unsupported flag $1" >&2
    exit 1
    ;;
  *) # preserve positional arguments
    PARAMS="$PARAMS $1"
    shift
    ;;
  esac
done

_sysname=$(uname)

if [ "${_sysname}" == "Darwin" ]; then
  threadCount=$(sysctl -a machdep.cpu | grep thread_count | awk '{print $2}')
else
  cpusCnt=$(lscpu | grep -E '^CPU\(' | awk '{print $2}') # cpus count
  tpcpu=$(lscpu | grep -E '^Thread' | awk '{print $4}')  # threads per core
  threadCount=$((cpusCnt * tpcpu))
fi

# create build root if not exists and go inside
mkdir -p ${BUILD_ROOT} && cd ${BUILD_ROOT}

# if need to test project only
if [ "${TEST_ONLY}" == "1" ]; then
  # delete everything inside just if build root already used
  rm -rf ./*
  cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_CONAN=Off -D${TEST_OPTION}=On
  make -j ${threadCount}
  make test
  exit 0
fi

if [ "${TYPE}" == "" ]; then
  echo "Please select type to build: archive or package"
  exit 1
fi

if [ "${TYPE}" == "archive" ]; then
  INTERNAL_OPTS="-DPACKAGE_ARCHIVE=On"
fi

rm -rf ./*
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_CONAN=Off -DENABLE_TEST=Off ${INTERNAL_OPTS} ${CMAKE_OPTS}

if [ "${DRY_RUN}" != "1" ]; then
  make -j ${threadCount}
  make package
fi
