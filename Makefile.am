# Specify the name of the program
bin_PROGRAMS = kleuren

ACLOCAL_AMFLAGS = $($ACLOCAL_AMFLAGS -I m4)

# Include the right headers for kleuren, cxxopts and dbgfm
kleuren_CPPFLAGS = $(INC_CPPFLAGS)

# Build all of the kleuren source files
kleuren_SOURCES = src/args.cpp src/arg_parse.cpp src/driver.cpp src/main.cpp \
				  src/color.cpp src/color_set.cpp src/color_manager.cpp  src/bubble_manager.cpp \
				  src/path.cpp src/bubble.cpp src/bubble_builder.cpp src/kmer_bank.cpp

# Link dbgfm library to kleuren 
kleuren_LDADD = thirdparty/dbgfm/libdbgfm.a

# Create the kleuren static library
noinst_LTLIBRARIES = libkleuren.la
libkleuren_la_CPPFLAGS = $(INC_CPPFLAGS)
libkleuren_la_SOURCES = src/args.cpp src/arg_parse.cpp src/driver.cpp \
				  src/color.cpp src/color_set.cpp src/color_manager.cpp src/bubble_manager.cpp \
				  src/path.cpp src/bubble.cpp src/bubble_builder.cpp src/kmer_bank.cpp
