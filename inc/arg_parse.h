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

#include <args.hxx>

#include "args.h"

class ArgParse {

    public:
        /// Parse the incoming arguments and return Args
        Args parseArgs(int argc, char* argv[]);

    private:

        /// The holder class for all of the parse arguments
        Args args;
};

#endif // ARG_PARSE_H
