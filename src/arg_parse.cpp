/*
 * Implementation of arge_parse.h
 */

#include <iostream>

#include "arg_parse.h"

using std::cout;
using std::endl;

class ArgParse {

    public:
        
        Args parseArgs(int argc, char* argv[]) {
            Args args = Args();
            
            try {
                Options options("kleuren", "A colored de Bruijn graph implementation using dbgfm.");

                // set up each argument
                options.add_options()
                    ("c,colors", "Path to the file that holds the paths to the individual colors.",
                        cxxopts::value<string>())
                    ("k,kmer_len", "Kmer length to use when querying the colors.", cxxopts::value<size_t>(),
                        "31")
                    ("h,help", "Print help")
                ;

                // parse the positional arguments
                options.parse_positional({"colors"});

                // parse the arguments
                options.parse(argc, argv);

                // print the help menu
                if(options.count("help")) {
                    cout << options.help() << endl;
                    exit(0);
                }

                /*
                 * Set the required arguments.
                 */


                /*
                 * Set the optional arguments.
                 */


            } catch(const cxxopts::OptionsException& e) {
                cout << "Error parsing options: " << e.what() << endl;
                exit(1);
            }

            return args;
        }

}
