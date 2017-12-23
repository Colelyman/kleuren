/*
 * Test cases for BubbleBuilder.
 */

#include "catch.hpp"

#include "bubble_builder.h"

#include <iostream>

using std::cout;
using std::endl;
using std::make_shared;

TEST_CASE("BubbleBuilder simple toy examples", "[bubble]") {
    Graph graph = Graph();
    BubbleBuilder bb = BubbleBuilder(&graph);
    string pathToToy1 = "./data/toy1.bwtdisk";
    string pathToToy2 = "./data/toy2.bwtdisk";
    string pathToToy3 = "./data/toy3.bwtdisk";
    string pathToToy4 = "./data/toy4.bwtdisk";
    shared_ptr<Color> toyColor1(new Color(1, "toyColor1", pathToToy1));
    shared_ptr<Color> toyColor2(new Color(2, "toyColor2", pathToToy2));
    shared_ptr<Color> toyColor3(new Color(3, "toyColor3", pathToToy3));
    shared_ptr<Color> toyColor4(new Color(4, "toyColor4", pathToToy4));

    SECTION("Finding a simple endKmer of two colors with a single SNP, that turns out to be a loop") {
        Vertex startVertex = Vertex("AAA", toyColor1->getBitVector());
        Vertex endVertex = Vertex("AAA", toyColor1->getBitVector());
        REQUIRE(bb.findEndVertex(startVertex, 4) == endVertex);
    }

    /*
    SECTION("Finding the endKmer between toy 3 and toy 4 colors") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        ColorSet colors = ColorSet(set<shared_ptr<Color> >({toyColor3, toyColor4}));
        REQUIRE(bb.findEndVertex(startKmer, toyColor3, colors) == endKmer);
        REQUIRE(bb.findEndVertex(startKmer, toyColor4, colors) == endKmer);
    }

    SECTION("Extending a simple linear path") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path3 = "CTGCAAT";
        REQUIRE(bb.extendPath(startKmer, endKmer, toyColor3, 10) == path3);
    }

    SECTION("Extending a simple branching path") {
        string startKmer = "CTG";
        string endKmer = "AAT";
        string path4 = "CTGAAT";
        REQUIRE(bb.extendPath(startKmer, endKmer, toyColor4, 10) ==  path4);
    }

}

TEST_CASE("BubbleBuilder virus examples", "[bubble]") {
    BubbleBuilder bb = BubbleBuilder();
    string pathToEbola = "./data/ebola.bwtdisk";
    string pathToFlu = "./data/flu.bwtdisk";
    string pathToMarburg = "./data/marburg.bwtdisk";
    string pathToZika = "./data/zika.bwtdisk";
    shared_ptr<Color> ebolaColor(new Color(1, "ebola", pathToEbola));
    shared_ptr<Color> fluColor(new Color(2, "flu", pathToFlu));
    shared_ptr<Color> marburgColor(new Color(3, "marburg", pathToMarburg));
    shared_ptr<Color> zikaColor(new Color(4, "zika", pathToZika));

    ColorSet colors = ColorSet(set<shared_ptr<Color> >({ebolaColor, fluColor, marburgColor, zikaColor}), 4);

    */
    /*SECTION("Finding an endKmer and extending a small path in the viruses") {
        string startKmer = "ATTACA";
        string endKmer = "TACAAA";
        REQUIRE(bb.findEndVertex(startKmer, ebolaColor, colors) == endKmer);
        
        unsigned int maxDepth = 5;
        string path = "ATTACAAA";
        CHECK(bb.extendPath(startKmer, endKmer, ebolaColor, maxDepth) == path);
        
        CHECK(bb.extendPath(startKmer, endKmer, fluColor, maxDepth) == path);

        CHECK(bb.extendPath(startKmer, endKmer, marburgColor, maxDepth) == path);

        CHECK(bb.extendPath(startKmer, endKmer, zikaColor, maxDepth) == path);
    }

    SECTION("Finding an endkmer and extending a longer path in the viruses") {
        string startKmer = "ATGCC";
        string endKmer = "GCCAA";
        
        REQUIRE(bb.findEndVertex(startKmer, zikaColor, colors) == endKmer);

        unsigned int maxDepth = 10;

        cout << bb.extendPath(startKmer, endKmer, marburgColor, maxDepth) << endl;
    }*/
}
