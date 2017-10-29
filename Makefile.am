# Specify the name of the program
bin_PROGRAMS = kleuren

#ACLOCAL_AMFLAGS = $($ACLOCAL_AMFLAGS -I m4)

# Include the right headers for kleuren, cxxopts and dbgfm
kleuren_CPPFLAGS = $(INC_CPPFLAGS)

# Build all of the kleuren source files
kleuren_SOURCES = src/args.cpp src/arg_parse.cpp src/driver.cpp src/main.cpp \
				  src/color.cpp src/color_set.cpp src/color_manager.cpp src/bubble_manager.cpp \
				  src/path.cpp src/bubble.cpp src/bubble_builder.cpp src/kmer_bank.cpp src/graph.cpp \
				  src/vertex.cpp src/graph_builder.cpp \
				  inc/args.h inc/arg_parse.h inc/driver.h inc/color.h inc/color_manager.h \
				  inc/color_set.h inc/bubble_manager.h inc/path.h inc/bubble_builder.h inc/bubble.h \
				  inc/kmer_bank.h inc/graph.h inc/vertex.h inc/graph_builder.h

# add the extra files for the distribution
EXTRA_DIST = thirdparty/cxxopts/include/cxxopts.hpp thirdparty/dbgfm/*

# Link dbgfm library to kleuren 
kleuren_LDADD = thirdparty/dbgfm/libdbgfm.a thirdparty/sdsl-lite/bin/lib/libsdsl.a

# Create the kleuren static library
noinst_LTLIBRARIES = libkleuren.la
libkleuren_la_CPPFLAGS = $(INC_CPPFLAGS)
libkleuren_la_SOURCES = src/args.cpp src/arg_parse.cpp src/driver.cpp \
						src/color.cpp src/color_set.cpp src/color_manager.cpp src/bubble_manager.cpp \
						src/path.cpp src/bubble.cpp src/bubble_builder.cpp src/kmer_bank.cpp src/graph.cpp \
						src/vertex.cpp src/graph_builder.cpp

