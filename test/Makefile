INCLUDES=-I../inc -Ithirdparty/catch -I../thirdparty/dbgfm
LIBS=-Lthirdparty/dbgfm -ldbgfm
CXXFLAGS=-g -std=c++11 -Wall $(INCLUDES) #$(LIBS)

.PHONY: all clean install main kleuren-test

TESTS_CPP:=$(wildcard src/*.cpp)
TESTS_O:=$(wildcard src/*.o)
SRC:=$(wildcard ../src/kleuren-*.o)

kleuren-test: $(TESTS_CPP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

clean:
	rm -f kleuren-test ./src/$(TESTS_O) 

src/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ 
