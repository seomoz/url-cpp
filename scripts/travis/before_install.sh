#! /usr/bin/env bash

set -e

sudo apt-get install -y g++ libgtest-dev cmake python-pip

sudo pip install gcovr==3.2

pushd /usr/src/gtest
    sudo CXX=g++ CC=gcc cmake CMakeLists.txt
    sudo CXX=g++ CC=gcc make
    find /usr/src/gtest -name '*.a' | xargs -I^ sudo ln -sf ^ /usr/lib
popd
