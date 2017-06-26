/**
 * This is the entry point into kleuren. It basically calls a
 * function to parse the arguments and then passes all of the 
 * logic off to the Driver.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 */

#include <iostream>

#include "arg_parse.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    cout << "Before argParse = ArgParse()" << endl;

    ArgParse argParse = ArgParse();

    argParse.parseArgs(argc, argv);

    cout << "After argParse.parseArgs()" << endl;

    return 0;
}
