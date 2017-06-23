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

};

#endif // ARG_PARSE_H
