# Specify the name of the program
bin_PROGRAMS = kleuren

# Include the right headers for kleuren and dbgfm
kleuren_CPPFLAGS = $(INC_CPPFLAGS)

# Build all of the kleuren source files
kleuren_SOURCES = src/args.cpp src/arg_parse.cpp src/main.cpp 

# Link dbgfm library to kleuren 
kleuren_LDADD = thirdparty/dbgfm/libdbgfm.a
