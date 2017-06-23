# Specify the name of the program
bin_PROGRAMS = kleuren

# Build all of the kleuren source files
kleuren_SOURCES = src/main.cpp

# Include both kleuren and dbgfm headers
include_HEADERS = inc/bubble.h inc/bubble_builder.h inc/color.h \
				  inc/color_manager.h inc/color_set.h inc/kmer_bank.h \
				  inc/path.h \
				  thirdparty/dbgfm/dbg_query.h thirdparty/dbgfm/fm_index.h

# Link kleuren to dbgfm library
kleuren_LIBRARIES = thirdparty/dbgfm/libdbgfm.a
kleuren_LDADD = thirdparty/dbgfm/libdbgfm.a
