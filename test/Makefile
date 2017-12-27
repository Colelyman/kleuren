INCLUDES=-I../inc -Ithirdparty/catch -I../thirdparty/dbgfm -I../thirdparty/sdsl-lite/bin/include
LIBS=-L../.libs -lkleuren -L../thirdparty/dbgfm -ldbgfm  -L../thirdparty/sdsl-lite/bin/lib -lsdsl
CXXFLAGS=-g -std=c++11 -Wall $(INCLUDES) $(LIBS)

.PHONY: all clean install main kleuren-test

TESTS_CPP=src/bubble_builder.cpp src/color_manager.cpp src/graph.cpp src/kmer_bank.cpp src/path.cpp
TESTS_O=src/main.o src/bubble_builder.o src/color_manager.o src/graph.o src/kmer_bank.o src/path.o

kleuren-test: src/main.o ../.libs/libkleuren.a $(TESTS_O)
	$(CXX) $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -f kleuren-test $(TESTS_O) 

src/main.o: src/main.cpp
	$(CXX) -c -Ithirdparty/catch -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 
