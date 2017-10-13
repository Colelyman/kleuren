INCLUDES=-I../inc -Ithirdparty/catch -I../thirdparty/dbgfm -I../thirdparty/sdsl-lite/bin/include
LIBS=-L../.libs -lkleuren -L../thirdparty/dbgfm -ldbgfm  -L../thirdparty/sdsl-lite/bin/lib -lsdsl
CXXFLAGS=-g -std=c++11 -Wall $(INCLUDES) $(LIBS)

.PHONY: all clean install main kleuren-test

TESTS_CPP:=$(filter-out src/main.cpp, $(wildcard src/*.cpp))
TESTS_O:=$(wildcard src/*.o)

kleuren-test: src/main.o $(TESTS_CPP)
	$(CXX) $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -f kleuren-test ./src/$(TESTS_O) 

src/main.o: src/main.cpp
	$(CXX) -c -Ithirdparty/catch -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)
