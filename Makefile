PARAMS = -g -Wall -O0 -fpermissive $(INC) $(LIBS) -fsanitize=address
INC = -I./inc -I./thirdparty/BloomFilterTrie/include -I./thirdparty/cxxopts/include
LIBS = -lbft -L./thirdparty/BloomFilterTrie/lib

EXEC = kleuren 
LIB = libkleuren.a
OBJS = src/args.o src/arg_parse.o src/driver.o src/main.o \
	src/color.o src/color_manager.o src/bubble_manager.o \
	src/path.o src/bubble.o src/bubble_builder.o src/kmer_bank.o src/graph.o 

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
