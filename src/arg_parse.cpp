/*
 * Implementation of arge_parse.h
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "arg_parse.h"

using std::cout;
using std::endl;
using std::exit;
using std::vector;
using std::string;

Args ArgParse::parseArgs(int argc, char* argv[]) {
    Options options("kleuren", "A colored de Bruijn graph implementation for phylogeny reconstruction using dbgfm.");

    this->args = Args();

    try {
        // set up each argument
        options.add_options()
            ("c,colorsFilePath", "Path to the file that holds the paths to the individual colors.",
                cxxopts::value<string>(), "PATH")
            ("k,kmerFilePath", "Path to the file that contains the kmers", cxxopts::value<string>(), "PATH")
            ("b,bubbleFilePath", "Path to the file in which to output the bubbles, if not provided bubbles will not be outputted", cxxopts::value<string>(), "PATH")
            ("m,matrixFilePath", "Path to the file in which to out the similarity matrix, if not provided the matrix will not be outputted", cxxopts::value<string>(), "PATH")
            ("n,numMinKmers", "The number of colors a kmer must be present in for a bubble to be formed. When set to 0, all colors must be present", cxxopts::value<unsigned int>()->default_value("0"), "INT")
            ("d,maxDepth", "The maximum depth for which to recursively extend paths for a bubble", cxxopts::value<unsigned int>()->default_value("200"), "INT")
            ("h,help", "Print help")
        ;

        // specify required arguments
        vector<string> required;
        required.push_back("colorsFilePath");
        required.push_back("kmerFilePath");

        // parse the arguments
        options.parse(argc, argv);

        // print the help menu
        if(options.count("help")) {
            cout << options.help() << endl;
            exit(0);
        }

        check_required(options, required);

        setArgs(options);

    } catch(const cxxopts::OptionException& e) {
        cout << options.help() << endl;
        cout << "Error parsing options: " << e.what() << endl;
        exit(1);
    }

    return args;
}

void ArgParse::setArgs(Options options) {
    args.setColorsFilePath(options["colorsFilePath"].as<string>());
    args.setKmerFilePath(options["kmerFilePath"].as<string>());
    if(options.count("bubbleFilePath") || options.count("b")) { // check if the bubbleFilePath parameter is present
        args.setBubbleFilePath(options["bubbleFilePath"].as<string>());
    }
    else {
        args.setBubbleFilePath("");
    }
    if(options.count("matrixFilePath") || options.count("m")) { // check if the matrixFilePath parameter is present
        args.setMatrixFilePath(options["matrixFilePath"].as<string>());
    }
    else {
        args.setMatrixFilePath("");
    }
    args.setN(options["numMinKmers"].as<unsigned int>());
    args.setMaxDepth(options["maxDepth"].as<unsigned int>());
}
