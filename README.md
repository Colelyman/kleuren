# kleuren
Find bubbles in the Colored de Bruijn Graph (CdBG) to reconstruct [phylogenetic
trees](https://en.wikipedia.org/wiki/Phylogenetic_tree).

[![Build Status](https://travis-ci.org/Colelyman/kleuren.svg?branch=master)](https://travis-ci.org/Colelyman/kleuren)

## Installation

`kleuren` uses the [CMake](https://cmake.org/) (>= version 3.1) build system to
compile and link its dependencies. Thus, in order to use `kleuren`, one must
have [CMake installed](https://cmake.org/install/).

### CMake on Ubuntu

If you have super-user priveleges then you can install CMake by running
``` sh
sudo apt-get install cmake
```
If you are running Ubuntu version 14.04 or earlier, then most likely the version
that you have installed is too old to be compatible with `kleuren` (< version
3.1). You can [download a CMake binary](https://cmake.org/download/) yourself,
or add a PPA to install a newer version of CMake via the following commands

``` sh
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get upgrade
```
and an up-to-date version of CMake will be installed for you.

### CMake on Mac OS X

If you have [Homebrew](https://brew.sh/) installed, then just run

``` sh
brew install cmake
```
and you are good to go!

### After CMake is Installed

Once CMake is installed, run the following commands to clone the `kleuren` repo
and compile the project
``` sh
git clone --recursive https://github.com/Colelyman/kleuren.git
cd kleuren
mkdir build
cd build && cmake ..
make
```
there will be the `kleuren` executable in the `./bin/` folder of the root
directory of the project. Thus, to run `kleuren` from the root directory of the
project, you can simply execute

``` sh
./bin/kleuren
```
and you have just run `kleuren`! 

If you need to link against `kleuren` to use it in your own program, then there
is also a static library in the `./bin` folder.

## Testing

`kleuren` uses the C++ unit-testing library
[catch](https://github.com/philsquared/Catch) to run unit tests. To run the test
suite, you can execute `./bin/kleuren_test`.

The data for the unit test is found in the `test/data/small` directory, and the
unit tests themselves are found in `test/src` directory.

## Using `kleuren`

`kleuren` depends on the
[BloomFilterTrie](https://github.com/GuilluameHolley/BloomFilterTrie) to represent
the CdBG. Thus, one must create the `BloomFilterTrie` representation of the CdBG
and pass that into `kleuren`. In order to create the CdBG one must count the
kmers of the genomes and pass that into `BloomFilterTrie`. 

There is a [scipipe](https://github.com/scipipe/scipipe) workflow available at
[kleuren-scipipe-workflow](https://github.com/Colelyman/kleuren-scipipe-workflow).
This will install `kleuren` and all of the other dependencies needed
(`BloomFilterTrie` and `jellyfish`) to run `kleuren` end-to-end, from genomes to
bubbles. If you would like to just see the steps needed to create the necessary
files, an example can be found in
[test/Makefile](https://github.com/Colelyman/kleuren/blob/master/test/Makefile).

## What's in a name?

*Kleuren* is the Dutch word for colors, which pays homage to the language of the
home country of the de Bruin graph's namesake, [Nicolaas Govert de
Bruijn](https://en.wikipedia.org/wiki/Nicolaas_Govert_de_Bruijn).
