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

Vertex::Vertex(string kmer) {
    this->kmer = kmer;
    this->bitsSet = false;
    this->colors = bit_vector();
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

string Vertex::bitsToString(bit_vector kmerBits, size_t kmerSize) {
    string kmer;
    unsigned char* baseBits = (unsigned char*) malloc(sizeof(char));
    for(int i = 0; i < kmerSize; i++) {
        int bitIndex = i * 2;
        memset(baseBits, 0, sizeof(unsigned char));
        *baseBits = (unsigned char) (kmerBits[bitIndex] << 1) | kmerBits[bitIndex + 1];
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
    free(baseBits);

    return kmer;
}

string Vertex::getKmer() const {
    return kmer;
}

bit_vector Vertex::getKmerBits() {
    kmerBits = bit_vector(kmer.length() * 2, 0);
    if(!bitsSet) {
        int r;
        // convert each nucleotide to bit encoding
        for(int i = 0; i < kmer.length(); i++) {
            int bitIndex = i * 2;
            switch(kmer.at(i)) {
            case 'A':
            case 'a':
                kmerBits[bitIndex++] = 1;
                kmerBits[bitIndex] = 0;
                break;
            case 'C':
            case 'c':
                kmerBits[bitIndex++] = 0;
                kmerBits[bitIndex] = 1;
                break;
            case 'G':
            case 'g':
                kmerBits[bitIndex++] = 1;
                kmerBits[bitIndex] = 1;
                break;
            case 'T':
            case 't':
                kmerBits[bitIndex++] = 0;
                kmerBits[bitIndex] = 0;
                break;
                /*
            case 'N':
            case 'n':
                kmerBits |= static_cast<BASES>(rand() % 4) << shift;
                break;
            case 'R': // A or G
            case 'r':
                kmerBits |= (rand() % 2 == 1) ? BASE_A << shift : BASE_G << shift;
                break;
            case 'Y': // C or T
            case 'y':
                kmerBits |= (rand() % 2 == 1) ? BASE_C << shift : BASE_T << shift;
                break;
            case 'S': // G or C
            case 's':
                kmerBits |= (rand() % 2 == 1) ? BASE_C << shift : BASE_G << shift;
                break;
            case 'W': // A or T
            case 'w':
                kmerBits |= (rand() % 2 == 1) ? BASE_A << shift : BASE_T << shift;
                break;
            case 'K': // G or T
            case 'k':
                kmerBits |= (rand() % 2 == 1) ? BASE_G << shift : BASE_T << shift;
                break;
            case 'M': // A or C
            case 'm':
                kmerBits |= (rand() % 2 == 1) ? BASE_C << shift : BASE_A << shift;
                break;
            case 'B': // C or G or T
            case 'b':
                r = rand() % 3;
                if(r == 1) {
                    kmerBits |= BASE_C << shift;
                }
                else if(r == 2) {
                    kmerBits |= BASE_G << shift;
                }
                else {
                    kmerBits |= BASE_T << shift;
                }
                break;
            case 'D': // A or G or T
            case 'd':
                r = rand() % 3;
                if(r == 1) {
                    kmerBits |= BASE_A << shift;
                }
                else if(r == 2) {
                    kmerBits |= BASE_G << shift;
                }
                else {
                    kmerBits |= BASE_T << shift;
                }
                break;
            case 'H': // A or C or T
            case 'h':
                r = rand() % 3;
                if(r == 1) {
                    kmerBits |= BASE_C << shift;
                }
                else if(r == 2) {
                    kmerBits |= BASE_A << shift;
                }
                else {
                    kmerBits |= BASE_T << shift;
                }
                break;
            case 'V': // A or C or G
            case 'v':
                r = rand() % 3;
                if(r == 1) {
                    kmerBits |= BASE_C << shift;
                }
                else if(r == 2) {
                    kmerBits |= BASE_G << shift;
                }
                else {
                    kmerBits |= BASE_A << shift;
                }
                break;
                */
            }
        }
        bitsSet = true;
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
