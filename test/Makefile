SIZE = small
GENOMES = ./data/$(SIZE)/1.kmers.txt ./data/$(SIZE)/2.kmers.txt \
		./data/$(SIZE)/3.kmers.txt ./data/$(SIZE)/4.kmers.txt

EXEC = ../bin/kleuren_test
BFT_EXEC = ../thirdparty/BloomFilterTrie/src/project_bft/bin/bft
COLORS := ./data/$(SIZE)/colors.txt
BFT_OUT := ./data/$(SIZE)/bft.out
KMERS := ./data/$(SIZE)/kmers.out
SRC = ./src/bubble_builder.cpp ./src/graph.cpp ./src/kmer_bank.cpp
JELLYFISH = ./thirdparty/jellyfish-1.1.12/bin/jellyfish

KMER_SIZE = 9

all: $(EXEC) $(BFT_OUT) test

$(EXEC): $(SRC)
	mkdir -p ../build
	cd ../build && cmake .. && make

$(BFT_OUT): $(COLORS) $(GENOMES)
	$(BFT_EXEC) build $(KMER_SIZE) kmers $(COLORS) $(BFT_OUT) -extract_kmers kmers $(KMERS)

test: $(EXEC) $(BFT_OUT)
	$(EXEC)

$(JELLYFISH):
	cd thirdparty && \
	tar zxf jellyfish-1.1.12.tar.gz && \
	cd jellyfish-1.1.12 && \
	./configure && \
	make -j 4

./data/$(SIZE)/%.kmers.txt: ./data/$(SIZE)/%.fasta
	 $(JELLYFISH) count -m $(KMER_SIZE) -s 1M -o $<.jf $<
	 $(JELLYFISH) dump -c $<.jf_0 -o $@

./data/$(SIZE)/super.kmers.txt:
	$(JELLYFISH) count -m $(KMER_SIZE) -s 5M -o ./data/$(SIZE)/super.kmers.jf ./data/$(SIZE)/*.fasta
	$(JELLYFISH) dump -c ./data/$(SIZE)/super.kmers.jf_0 -o $@

clean:
	rm $(BFT_OUT) $(EXEC)
