/*
 * Implementation of arge_parse.h
 */

#include <iostream>
#include <cstdlib>
#include <string>

#include "arg_parse.h"

using std::cout;
using std::cerr;
using std::endl;
using std::exit;
using std::string;

Args ArgParse::parseArgs(int argc, char* argv[]) {
    args::ArgumentParser parser("kleuren", "A colored de Bruijn graph implementation for phylogeny tree reconstruction.");
    args::Group required(parser, "Required parameters", args::Group::Validators::All);
    args::ValueFlag<string> bftFilePath(required, "Path to BFT file",
                                        "Path to the BloomFilterTrie generated file",
                                        {'f', "bftFilePath"});
    args::ValueFlag<string> kmerFilePath(required, "kmerFilePath",
                                         "Path to the file that contains the kmers",
                                         {'k', "kmerFilePath"});
    args::ValueFlag<string> bubbleFilePath(parser, "bubbleFilePath",
                                           "Path to the file in which to output the bubbles, if not provided bubbles will not be outputted",
                                           {'b', "bubbleFilePath"});
    args::ValueFlag<uint32_t> kmerLen(parser, "kmerLen",
                                      "The length of kmer to use in order to construct the Colored de Bruijn Graph",
                                      {'k', "kmerLen"},
                                      18);
    args::ValueFlag<uint32_t> numMinColors(parser, "numMinColors",
                                           "The number of colors a kmer must be present in for a bubble to be formed. When set to 0, all colors must be present",
                                           {'n', "numMinColors"},
                                           0);
    args::ValueFlag<uint32_t> maxDepth(parser, "maxDepth",
                                       "The maximum depth for which to recursively extend paths for a bubble",
                                       {'d', "maxDepth"},
                                       30);
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    try {
        parser.ParseCLI(argc, argv);
    } catch(args::Help) {
        cout << parser;
        exit(1);
    } catch(args::ValidationError e) {
        cerr << e.what();
        cerr << " bftFilePath and kmerFilePath are both required." << endl;
        if(!bftFilePath) {
            cerr << "bftFilePath is not provided." << endl;
        }
        if(!kmerFilePath) {
            cerr << "kmerFilePath is not provided." << endl;
        }
        cerr << parser;
        exit(1);
    } catch(args::ParseError e) {
        cerr << e.what() << endl;
        cerr << parser;
        exit(1);
    }

    args.setBFTFilePath(args::get(bftFilePath));
    args.setKmerFilePath(args::get(kmerFilePath));
    if(bubbleFilePath) {
        args.setBubbleFilePath(args::get(bubbleFilePath));
    }
    else {
        args.setBubbleFilePath("");
    }
    args.setKmerLen(args::get(kmerLen));
    args.setN(args::get(numMinColors));
    args.setMaxDepth(args::get(maxDepth));

    return args;
}

