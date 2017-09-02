#!/bin/bash

# This script sets up everything necessary for kleuren
# and installs it and the third party dependencies.

echo "Retrieve the thirdparty dependecies.\n"

git submodule update --init --recursive

echo "Build dbgfm.\n"

cd thirdparty/dbgfm && make && cd -

echo "Create configure file by autoreconf --install.\n"

autoreconf --install

echo "Build the Makefiles tailored to your system by ./configure.\n"

./configure

echo "Install kleuren by make.\n"

make

echo "Create conda environment if conda is installed.\n"

if hash conda 2>/dev/null; then
    # create the environment
    conda env create -f environment.yml
    # activate the envirnoment
    source activate kleuren
fi

echo "Finished, run make install to put kleuren in your path or add $PWD to your PATH variable."
