# Specify the name of the program
bin_PROGRAMS = kleuren

# Include the right headers for kleuren, cxxopts and dbgfm
kleuren_CPPFLAGS = $(INC_CPPFLAGS)

# Build all of the kleuren source files
kleuren_SOURCES = src/args.cpp src/arg_parse.cpp src/driver.cpp src/main.cpp \
				  src/color.cpp src/color_set.cpp src/color_manager.cpp \
				  src/path.cpp src/bubble.cpp src/bubble_builder.cpp src/kmer_bank.cpp

# Link dbgfm library to kleuren 
kleuren_LDADD = thirdparty/dbgfm/libdbgfm.a
