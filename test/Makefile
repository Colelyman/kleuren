EXEC = ../bin/kleuren_test
BFT_EXEC = ../thirdparty/BloomFilterTrie/src/project_bft/bin/bft
COLORS = ./data/colors.txt
BFT_OUT = ./data/bft.out
KMERS = ./data/kmers.out
SRC = ./src/bubble_builder.cpp ./src/graph.cpp ./src/kmer_bank.cpp

all: $(EXEC) $(BFT_OUT) test

$(EXEC): $(SRC)
	mkdir -p ../build
	cd ../build && cmake .. && make

$(BFT_OUT): $(COLORS)
	$(BFT_EXEC) build 18 kmers $(COLORS) $(BFT_OUT) -extract_kmers kmers $(KMERS)

test: $(EXEC) $(BFT_OUT)
	$(EXEC)

clean:
	rm $(BFT_OUT) $(EXEC)
