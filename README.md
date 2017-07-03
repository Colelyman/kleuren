# kleuren
A colored de Bruijn graph implementation using the `dbgfm` library as the underlying de Bruijn graph structure.

## Installation

### Regular Use

**Coming soon...**

### Development

To install `kleuren` with the intent to develop it, one must follow these steps:

1. Get the code. Clone the repository from Github by running the following command: `git clone https://github.com/Colelyman/kleuren.git`, and then move into the project folder `cd kleuren`.
2. Get the Third Party dependencies. To get the dependencies, run: `git submodule update --init --recursive`.
    1. Install `dbgfm`. First go to the `dbgfm` directory: `cd thirdparty/dbgfm`, then install: `make`.
3. Setup the installation. `kleuren` uses [autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) to maximize the portability of the project. Here are the steps to get the project configured:
    1. Run `autoreconf --install`, which will install any missing tools and set up the build environment.
    2. Run `./configure`, which will create a `Makefile` (among other files) that is tailored to your system.
    3. Run `make`, which will install the `kleuren` library (which is found in `./.libs/libkleuren.a`) and the kleuren binary (which is found in `./kleuren`).
    4. Run `./kleuren` to actually run `kleuren`.
4. *Optional:* If one would like to run `kleuren` from anywhere on one's system, run `sudo make install`. In order for this to work one must have super-user privileges. One could also add the path to the directory in which `kleuren` is install to one's `PATH` variable, like this: `export PATH=$PATH:<path to where kleuren is installed>`.
5. Go forth and develop! 

### Testing

`kleuren` uses the C++ unit-testing library [catch](https://github.com/philsquared/Catch) to run unit tests.
To install the test cases, one must first follow the instructions above to install `kleuren` itself. Then one must move to the test directory: `cd test` and install the unit test: `make`.

The data for the unit test is found in the `test/data` directory, and the unit tests themselves are found in `test/src` directory.

## What's in a name?

*Kleuren* is the Dutch word for colors, which pays homage to the language of the home country of the de Bruin graph's namesake, [Nicolaas Govert de Bruijn](https://en.wikipedia.org/wiki/Nicolaas_Govert_de_Bruijn).
