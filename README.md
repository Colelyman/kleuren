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

