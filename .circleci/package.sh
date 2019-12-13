#!/usr/bin/env bash
rm -rf _build_package && mkdir _build_package

cd _build_package

mkdir _build
mkdir _install
mkdir _output

BOOST_HASH=$(conan info boost/1.70.0@conan/stable | grep ID | head -n1 | awk '{print $2}')
CONAN_BOOST_PREFIX=${HOME}/.conan/data/boost/1.70.0/conan/stable/package/${BOOST_HASH}

cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_CONAN=Off -DBOOST_ROOT=${CONAN_BOOST_PREFIX} -DENABLE_SHARED=On -DCMAKE_INSTALL_PREFIX=$(pwd)/_install
cmake --build . -- -j4
cmake --build . --target install

function to_lower() {
  local outRes=$(echo ${1} | awk '{ for ( i=1; i <= NF; i++) {   sub(".", substr(tolower($i),1,1) , $i)  } print }')
  echo "${outRes}"
}

tar_bin=$(which tar | tr -d "\n")
if [ "${tar_bin}" == "" ]
then
  echo "Tar executable not found!"
  exit 1
fi

VERS=`git rev-parse --short HEAD`
if [ -f "version" ]
then
    VERS=`cat version | tr -d "\n"`
fi

if [ -f "../version" ]
then
    VERS=`cat ../version | tr -d "\n"`
fi

if [ "${1}" != "" ]
then
    VERS=${1}
fi

arch=$(uname -m)
sysname=$(uname)
sysname=$(to_lower ${sysname})
ghash=$(git rev-parse --short=8 HEAD)
fname_sufix="v${VERS}-${ghash}-${sysname}-${arch}"
fname="libminter_tx-${fname_sufix}.tar.gz"

cd $(pwd)/_install

tar -zcvf ${fname} .

mv ${fname} ../_output
cd ../_output

ls -lsa $(pwd)

echo "Uploading file ${fname} to GH"
ghr ${VERS} .










