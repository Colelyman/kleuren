/*
 * Test cases for KmerBank.
 */

#include "catch.hpp"

#include "kmer_bank.h"

TEST_CASE("Testing the method getNextKmer", "[KmerBank]") {
    ifstream kmerFile;
    kmerFile.open("data/super_viruses.kmers.txt");

    KmerBank kmerBank = KmerBank(&kmerFile);
    REQUIRE(kmerBank.getNextKmer() == "AAAAAAACAATATTTGA");
    REQUIRE(kmerBank.getNextKmer() == "AAAAAACAAAGAGTGAA");
    REQUIRE(kmerBank.getNextKmer() == "AAAAAACAATATTTGAA");

    kmerFile.close();
}
