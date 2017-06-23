/**
 * @class ArgParse
 *
 * The sole purpose of this class is to parse arguments and pass
 * them to the Driver.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 *
 */

#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include <cxxopts.hpp>

#include "args.h"

using cxxopts::Options;

class ArgParse {

    public:
        /// Parse the incoming arguments and return Args
        Args parseArgs(int argc, char* argv[]);

    private:
        /// Helper method to set the required arguments
        void setRequriedArgs();

        /// Helper method to set the optional arguments
        void setOptionalArgs();

        /// The object used by cxxopts to parse the arguments
        Options options;

        /// The holder class for all of the parse arguments
        Args args;
};

#endif // ARG_PARSE_H
