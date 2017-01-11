#! /usr/bin/env bash

set -e

sudo apt-get install -y clang-3.5 g++ libgtest-dev cmake python-pip

sudo pip install gcovr==3.2

pushd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    find /usr/src/gtest -name '*.a' | xargs -I^ sudo ln -sf ^ /usr/lib
popd
