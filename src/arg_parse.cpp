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
    Options options("kleuren", "A colored de Bruijn graph implementation for phylogeny tree reconstruction.");

    this->args = Args();

    try {
        // set up each argument
        options.add_options()
            ("f,bftFilePath", "Path to the BloomFilterTrie generated file.",
                cxxopts::value<string>(), "PATH")
            ("k,kmerFilePath", "Path to the file that contains the kmers", cxxopts::value<string>(), "PATH")
            ("b,bubbleFilePath", "Path to the file in which to output the bubbles, if not provided bubbles will not be outputted", cxxopts::value<string>(), "PATH")
            ("l,kmerLen", "The length of kmer to use in order to construct the Colored de Bruijn Graph", cxxopts::value<uint32_t>()->default_value("18"), "INT") 
            ("n,numMinColors", "The number of colors a kmer must be present in for a bubble to be formed. When set to 0, all colors must be present", cxxopts::value<uint32_t>()->default_value("0"), "INT")
            ("d,maxDepth", "The maximum depth for which to recursively extend paths for a bubble", cxxopts::value<uint32_t>()->default_value("30"), "INT")
            ("h,help", "Print help")
        ;

        // specify required arguments
        vector<string> required;
        required.push_back("bftFilePath");
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
    args.setBFTFilePath(options["bftFilePath"].as<string>());
    args.setKmerFilePath(options["kmerFilePath"].as<string>());
    if(options.count("bubbleFilePath") || options.count("b")) { // check if the bubbleFilePath parameter is present
        args.setBubbleFilePath(options["bubbleFilePath"].as<string>());
    }
    else {
        args.setBubbleFilePath("");
    }
    args.setKmerLen(options["kmerLen"].as<uint32_t>());
    args.setN(options["numMinColors"].as<uint32_t>());
    args.setMaxDepth(options["maxDepth"].as<uint32_t>());
}
