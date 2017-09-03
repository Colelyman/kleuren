/*
 * Test cases for Path.
 */

#include "catch.hpp"

#include "path.h"

TEST_CASE("Path operations", "[path]") {
    // the color doesn't matter much for these test cases
    Color zikaColor = Color(1, "zikaColor", "./data/zika.bwtdisk");

    SECTION("Shared Kmer Count") {
        Path path1 = Path("ACT");
        Path path2 = Path("TTG");

        REQUIRE(path1.runSharedKmerCount(path2, 3) == 0);

        Path path3 = Path("ACTGTCAGTGCAGTACAGTAACAAA");
        Path path4 = Path("ACTGGCAGGGCACTATAGTAACAAT");

        REQUIRE(path3.runSharedKmerCount(path4, 5) == 4);

        // Test the edge case to make sure the for loop gets the last kmer
        Path path5 = Path("ACTGTCAGTGCAGTACAGTAACAAA");
        Path path6 = Path("ACTGGCAGGGCACTATAGTAACAAA");

        REQUIRE(path5.runSharedKmerCount(path6, 5) == 5);
    }
}
