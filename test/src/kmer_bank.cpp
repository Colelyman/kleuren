/*
 * Test cases for KmerBank.
 */

#include "catch.hpp"

#include "kmer_bank.h"

TEST_CASE("Testing the method getNextKmer", "[KmerBank]") {
    ifstream kmerFile;
    kmerFile.open("data/small/kmers.out");

    KmerBank kmerBank = KmerBank(&kmerFile);

    REQUIRE(kmerBank.getNextKmer() == "CTAACACAT");
    REQUIRE(kmerBank.getNextKmer() == "CTAACACCT");
    REQUIRE(kmerBank.getNextKmer() == "CTAACACTT");

    kmerFile.close();
}
