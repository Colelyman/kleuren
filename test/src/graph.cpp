/*
 * Test cases for Graph.
 */

#include "catch.hpp"
#include <iostream>

#include "graph.h"

using std::cout;
using std::endl;

uint32_t Graph::kmerLen;

TEST_CASE("Graph simple vertex additions", "[graph]") {
    SECTION("Testing isVertex() method") {
        Graph::kmerLen = 5;
        
        Graph g = Graph();
        bit_vector b1 = {0, 1, 0, 0};
        Vertex v1 = Vertex("ACTGT", b1);
        g.addVertex(v1);
        REQUIRE(g.isVertex(v1));

        bit_vector b2 = {1, 0, 0, 0};
        Vertex v2 = Vertex("ACTGT", b2);
        REQUIRE(!g.isVertex(v2));

        bit_vector b3 = {1, 1, 0, 0};
        Vertex v3 = Vertex("ACTGT", b3);
        REQUIRE(g.isVertex(v3));

        Vertex v4 = Vertex("ACTGG", b3);
        REQUIRE(!g.isVertex(v4));
    }

    SECTION("Testing getSuffixNeighbors() method") {
        Graph g = Graph();
        bit_vector b1 = {0, 0, 0, 1};
        Vertex v1 = Vertex("AACCT", b1);
        g.addVertex(v1);
        Vertex v2 = Vertex("ACCTG", b1);
        g.addVertex(v2);
        Vertex v3 = Vertex("ACCTT", b1);
        g.addVertex(v3);
        vector<Vertex> vertices1;
        vertices1.push_back(v2);
        vertices1.push_back(v3);
        vector<Vertex> vertices2 = g.getSuffixNeighbors(v1);
        REQUIRE(vertices1 == vertices2);

        bit_vector b2 = {0, 0, 1, 0};
        Vertex v4 = Vertex("ACCTC", b2);
        vector<Vertex> vertices3 = {};
        vector<Vertex> vertices4 = g.getSuffixNeighbors(v4);
        REQUIRE(vertices3 == vertices4);
    }

    SECTION("Testing getPrefixNeighbors() method") {
        Graph::kmerLen = 6;

        Graph g = Graph();
        bit_vector b1 = {0, 1, 0, 0};
        Vertex v1 = Vertex("TTACTN", b1);
        g.addVertex(v1);
        Vertex v2 = Vertex("ATTACT", b1);
        g.addVertex(v2);
        Vertex v3 = Vertex("GTTACT", b1);
        g.addVertex(v3);
        vector<Vertex> vertices1;
        vertices1.push_back(v2);
        vertices1.push_back(v3);
        vector<Vertex> vertices2 = g.getPrefixNeighbors(v1);
        REQUIRE(vertices1 == vertices2);
    }
}
