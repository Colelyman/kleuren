/**
 * This is the entry point into kleuren. It basically calls a
 * function to parse the arguments and then passes all of the 
 * logic off to the Driver.
 *
 * @author Cole Lyman
 *
 * @date 2017/6/22
 */

#include "arg_parse.h"
#include "driver.h"

int main(int argc, char* argv[]) {

    ArgParse argParse = ArgParse();
    Driver driver = Driver();

    driver.run(argParse.parseArgs(argc, argv));

    return 0;
}
