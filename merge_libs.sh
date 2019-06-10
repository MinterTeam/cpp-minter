#!/usr/bin/env bash

BPATH=$1
LIBNAME=$2

cd ${BPATH}

for file in *.a;
do
 ar -x ${file}
done

ar -qc lib${LIBNAME}.a *.o
rm -rf *.o