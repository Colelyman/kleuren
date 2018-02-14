INCLUDES = -I../inc -Ithirdparty/catch -I../thirdparty/BloomFilterTrie/include
LIBS = -L.. -lkleuren -L../thirdparty/BloomFilterTrie/lib -lbft
CXXFLAGS = -g -std=c++11 -Wall -fpermissive $(INCLUDES) $(LIBS)

EXEC = kleuren-test
TESTS_O = src/main.o src/bubble_builder.o src/color_manager.o src/graph.o src/kmer_bank.o src/path.o

all: $(EXEC)

$(EXEC): $(TESTS_O) src/main.o ../libkleuren.a
	$(CXX) $^ $(CXXFLAGS) -o $@

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TESTS_O) $(EXEC)

