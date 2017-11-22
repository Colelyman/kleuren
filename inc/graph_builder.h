/**
 * @class GraphBuilder
 * 
 * GraphBuilder parses through FASTA files and adds kmers to the graph.
 *
 * @author Cole Lyman
 *
 * @date 2017/10/28
 *
 */

#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include <fstream>
#include <string>

#include "graph.h"

using std::ifstream;
using std::string;

class GraphBuilder {

   public:

       GraphBuilder(Graph* graph, unsigned int kmerLen);

       void addColor(string filePath, bit_vector color);
       
   private:

       void parseFasta(string filePath, bit_vector color);

       void addSequence(string prev, string line, bit_vector color);
       
       /// Pointer to the graph object.
       Graph* graph;

       /// The length of kmer to add to the graph.
       unsigned int kmerLen;

};

#endif // GRAPH_BUILDER_H

