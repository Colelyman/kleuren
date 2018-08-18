/*
 * Test cases for AbstractGraph
 */

#include "catch.hpp"

#include "abstract_graph.h"

TEST_CASE("AbstractGraph testing", "[graph]") {
    char* graphPath = (char*) malloc(100);
    strcpy(graphPath, "./data/small/bft.out");
    Graph* graph = new Graph(graphPath);
    AbstractGraph* abstractGraph = new AbstractGraph(graph);
    SECTION("Test doTopologicalOrdering") {
        string dependencies = "a b c\nd\ne f\nb c d e\n";
        string ordering = abstractGraph->doTopologicalOrdering(dependencies);
        REQUIRE(ordering == "a\nb\nc\nd\ne\nf\n");

        // check if doToloplogicalOrdering properly handles loops (or other errors)
        dependencies = "a b\nb a";
        ordering = abstractGraph->doTopologicalOrdering(dependencies);
        REQUIRE(ordering == "");
    }

    delete graph;
    delete abstractGraph;
}

