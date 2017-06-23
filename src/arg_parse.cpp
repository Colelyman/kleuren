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
            args = Args();
            
            try {
                // set up each argument
                options.add_options()
                    ("c,colorsFilePath", "Path to the file that holds the paths to the individual colors.",
                        cxxopts::value<string>())
                    ("k,kmerLen", "Kmer length to use when querying the colors.", cxxopts::value<size_t>(),
                        "31")
                    ("h,help", "Print help")
                ;

                // parse the positional arguments
                options.parse_positional({"colorsFilePath"});

                // parse the arguments
                options.parse(argc, argv);

                // print the help menu
                if(options.count("help")) {
                    cout << options.help() << endl;
                    exit(0);
                }

                setRequiredArgs();

                setOptionalArgs();

            } catch(const cxxopts::OptionsException& e) {
                cout << "Error parsing options: " << e.what() << endl;
                exit(1);
            }

            return args;
        }

    private:

        void setRequiredArgs() {
            args.setColorsFilePath(options["colorsFilePath"].as<string>());
            args.setKmerLen(options["kmerLen"].as<size_t>());
        }

        void setOptionalArgs() {

        }

        Options options("kleuren", "A colored de Bruijn graph implementation using dbgfm.");

        Args args;
}
