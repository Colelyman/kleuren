/*
 * Implementation of vertex.h.
 */

#include "vertex.h"

#include <stdlib.h>
#include <stdio.h>

// binary values for each base, these are the encodings used in the .2bit file format
enum BASES {
    BASE_T = 0x0, // binary: 00
    BASE_C = 0x1, // binary: 01
    BASE_A = 0x2, // binary: 10
    BASE_G = 0x3, // binary: 11
    BASE_MASK = 0x3 // binary: 11
};

Vertex::Vertex(string kmer, size_t numColors) {
    this->kmer = kmer;
    this->bitsSet = false;
    this->colors = bit_vector(numColors, 1);
}

Vertex::Vertex(string kmer, bit_vector colors) {
    this->kmer = kmer;
    this->bitsSet = false;
    this->colors = colors;
}

Vertex::~Vertex() {

}

bool Vertex::operator==(const Vertex& v) const {
    if(this->kmer == v.kmer && this->colors == v.colors) {
        return true;
    }
    else {
        return false;
    }
}

bool Vertex::operator<(const Vertex& v) const {
	return this->kmer < v.kmer;
}

string Vertex::getKmer() const {
    return kmer;
}

string Vertex::bitsToString(const unsigned char* kmerBits, size_t kmerSize) {
    string kmer;
    unsigned char* baseBits = new unsigned char;
    for(int i = 0; i < kmerSize; i++) {
        size_t shift = 6 - 2 * (i % 4);
        unsigned char mask = BASE_MASK << shift;
        memset(baseBits, 0, sizeof(unsigned char));
        *baseBits = (unsigned char) (kmerBits[i / 4] & mask) >> shift;
        switch(*baseBits) {
        case BASE_A:
            kmer.append("A");
            break;
        case BASE_C:
            kmer.append("C");
            break;
        case BASE_G:
            kmer.append("G");
            break;
        case BASE_T:
            kmer.append("T");
            break;
        }
    }
    delete baseBits;

    return kmer;
}

const unsigned char* Vertex::getKmerBits(string kmer) {
    size_t numBytes = (kmer.length() / 4) + (kmer.length() % 4 != 0);
    unsigned char* bits = new unsigned char[numBytes];
    memset(bits, 0, numBytes);
    int r;
    // convert each nucleotide to bit encoding
    for(int i = 0; i < kmer.length(); i++) {
        size_t shift = 6 - 2 * (i % 4);
        switch(kmer.at(i)) {
        case 'A':
        case 'a':
            bits[i / 4] |= BASE_A << shift;
            break;
        case 'C':
        case 'c':
            bits[i / 4] |= BASE_C << shift;
            break;
        case 'G':
        case 'g':
            bits[i / 4] |= BASE_G << shift;
            break;
        case 'T':
        case 't':
            bits[i / 4] |= BASE_T << shift;
            break;
        case 'N':
        case 'n':
            bits[i / 4] |= static_cast<BASES>(rand() % 4) << shift;
            break;
        case 'R': // A or G
        case 'r':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_A << shift : BASE_G << shift;
            break;
        case 'Y': // C or T
        case 'y':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_C << shift : BASE_T << shift;
            break;
        case 'S': // G or C
        case 's':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_C << shift : BASE_G << shift;
            break;
        case 'W': // A or T
        case 'w':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_A << shift : BASE_T << shift;
            break;
        case 'K': // G or T
        case 'k':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_G << shift : BASE_T << shift;
            break;
        case 'M': // A or C
        case 'm':
            bits[i / 4] |= (rand() % 2 == 1) ? BASE_C << shift : BASE_A << shift;
            break;
        case 'B': // C or G or T
        case 'b':
            r = rand() % 3;
            if(r == 1) {
                bits[i / 4] |= BASE_C << shift;
            }
            else if(r == 2) {
                bits[i / 4] |= BASE_G << shift;
            }
            else {
                bits[i / 4] |= BASE_T << shift;
            }
            break;
        case 'D': // A or G or T
        case 'd':
            r = rand() % 3;
            if(r == 1) {
                bits[i / 4] |= BASE_A << shift;
            }
            else if(r == 2) {
                bits[i / 4] |= BASE_G << shift;
            }
            else {
                bits[i / 4] |= BASE_T << shift;
            }
            break;
        case 'H': // A or C or T
        case 'h':
            r = rand() % 3;
            if(r == 1) {
                bits[i / 4] |= BASE_C << shift;
            }
            else if(r == 2) {
                bits[i / 4] |= BASE_A << shift;
            }
            else {
                bits[i / 4] |= BASE_T << shift;
            }
            break;
        case 'V': // A or C or G
        case 'v':
            r = rand() % 3;
            if(r == 1) {
                bits[i / 4] |= BASE_C << shift;
            }
            else if(r == 2) {
                bits[i / 4] |= BASE_G << shift;
            }
            else {
                bits[i / 4] |= BASE_A << shift;
            }
            break;
        }
    }
    
    return bits;
}

const unsigned char* Vertex::getKmerBits() {
    if(!bitsSet) {
        kmerBits = getKmerBits(kmer);
    }
    return kmerBits;
}

bit_vector Vertex::getColors() const {
    return this->colors;
}

unsigned int Vertex::getNumColors() const {
	rank_support_v<> rs(&colors);
	return rs.rank(colors.size());
}
