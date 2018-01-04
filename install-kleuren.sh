#!/bin/bash

# This script sets up everything necessary for kleuren
# and installs it and the third party dependencies.

echo "Retrieve the thirdparty dependecies.\n"

git submodule update --init --recursive

echo "Build sdsl-lite.\n"

cd thirdparty/sdsl-lite && mkdir -p bin && ./install.sh bin && cd -

echo "Build bft.\n"
# edit the following variables if Judy and Jemalloc are not installed in the default location (aka you don't have superuser privileges)
JUDY_INSTALL_DIR=""
JEMALLOC_INSTALL_DIR=""
if [ -z "$JUDY_INSTALL_DIR" ] && [ -z "$JEMALLOC_INSTALL_DIR" ]
then
    export CPPFLAGS="-I$JUDY_INSTALL_DIR/include -I$JEMALLOC_INSTALL_DIR/include -L$JUDY_INSTALL_DIR/lib -L$JEMALLOC_INSTALL_DIR/lib"
    export LDFLAGS="-L$JUDY_INSTALL_DIR/lib -L$JEMALLOC_INSTALL_DIR/lib"
fi

cd thirdparty/BloomFilterTrie && \
    ./configure --prefix=$PWD && \
    make

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
