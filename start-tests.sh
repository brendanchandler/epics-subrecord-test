#!/bin/env bash

cd ${BASH_SOURCE##*/}

pushd subTestApp/src/O.linux-x86_64/
./testsub
popd
