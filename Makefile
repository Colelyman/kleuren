PARAMS = -g -Wall -O0 -fpermissive $(INC) $(LIBS)
INC = -I./inc -I./thirdparty/BloomFilterTrie/include -I./thirdparty/sdsl-lite/bin/include -I./thirdparty/cxxopts/include
LIBS = -lbft -L./thirdparty/BloomFilterTrie/lib -L./thirdparty/sdsl-lite/bin/lib -lsdsl

EXEC = kleuren 
LIB = libkleuren.a
OBJS = src/args.o src/arg_parse.o src/driver.o src/main.o \
	src/color.o src/color_manager.o src/bubble_manager.o \
	src/path.o src/bubble.o src/bubble_builder.o src/kmer_bank.o src/graph.o \
	src/vertex.o src/graph_builder.o
HDR = inc/args.h inc/arg_parse.h inc/driver.h inc/color.h inc/color_manager.h \
	inc/bubble_manager.h inc/path.h inc/bubble_builder.h inc/bubble.h \
	inc/kmer_bank.h inc/graph.h inc/vertex.h inc/graph_builder.h

all: $(EXEC) $(LIB)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(PARAMS)

src/%.o: src/%.cpp inc/%.h
	$(CXX) $(PARAMS) -c $< -o $@

src/main.o: src/main.cpp
	$(CXX) $(PARAMS) -c $< -o $@

$(LIB): $(OBJS)
	ar -cvq $@ $<

clean:
	rm $(OBJS) $(EXEC)
