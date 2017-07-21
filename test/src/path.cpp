/*
 * Test cases for Path.
 */

#include "catch.hpp"

#include "path.h"

TEST_CASE("Path operations", "[path]") {
    // the color doesn't matter much for these test cases
    Color zikaColor = Color(1, "zikaColor", "./data/zika.bwtdisk");

    SECTION("Shared Kmer Count") {
        Path path1 = Path(&zikaColor);
        Path path2 = Path(&zikaColor);

        string seq1 = "ACT";
        string seq2 = "TTG";
       
        path1.append(seq1);
        path2.append(seq2);

        REQUIRE(path1.runSharedKmerCount(path2, 3) == 0);

        Path path3 = Path(&zikaColor);
        Path path4 = Path(&zikaColor);

        string seq3 = "ACTGTCAGTGCAGTACAGTAACAAA";
        string seq4 = "ACTGGCAGGGCACTATAGTAACAAT";

        path3.append(seq3);
        path4.append(seq4);

        REQUIRE(path3.runSharedKmerCount(path4, 5) == 4);

        // Test the edge case to make sure the for loop gets the last kmer
        Path path5 = Path(&zikaColor);
        Path path6 = Path(&zikaColor);

        string seq5 = "ACTGTCAGTGCAGTACAGTAACAAA";
        string seq6 = "ACTGGCAGGGCACTATAGTAACAAA";

        path5.append(seq5);
        path6.append(seq6);

        REQUIRE(path5.runSharedKmerCount(path6, 5) == 5);
    }
}
