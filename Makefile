# Makefile for C and C++ projects

# Defines compiler
CC := gcc

# Defines the the srouce file extension
SourceExt := c
# Defines the header file extension
HeaderExt := h

# The binary name
Bin := bin

# Defines where are the source files
SourceDir := src
# Defines where are the files to be included (headers
IncludeDir := include
# Defines where will be the build files placed
BuildDir := build
# Defines where will the binary placed
BinDir := bin
# Dependencies of the files will be here
DepsDir := deps

# The compiler flags
CFlags := -g
# The libs to link
Libs := -lpthread

# List all the source files
Sources := $(shell find $(SourceDir) -type f -name *.$(SourceExt))

# Object files will be named as the sources but will be on BuildDir
Objects := $(patsubst $(SourceDir)/%.$(SourceExt), $(BuildDir)/%.o, $(Sources))

# All the dependencies will be like this
Deps := $(patsubst $(BuildDir)/%.o, $(DepsDir)/%.d, $(Objects))

# Making the bin depends on the objects
$(BinDir)/$(Bin): $(Objects)
	@mkdir -p bin
	$(CC) $(Objects) -o $(BinDir)/$(Bin) 

# Compiling each file
$(BuildDir)/%.o: $(SourceDir)/%.$(SourceExt)
	@mkdir -p build
	$(CC) $(CFlags) $(Libs) -I $(IncludeDir) -c $< -o $@

# Creates auto-dependencies of files
#$(DepsDir)/%.d: $(Sources)
#@ $(CC) $(CFlags) $(Libs) -MM $*.$(SourceExt) | sed 's@^\(.*\)\.o:@\1.d \1.o:@' > $@

# These rules make no file
.PHONY: clean

# These deletes all of the compilation intermediary files
clean:
	rm $(shell find $(BuildDir) -type f -name *.o) $(shell find $(DepsDir) -type f -name *.d)

ifneq "$(MAKECMDGOALS)" "clean"
	-include ${Sources:.$(SourceExt)=.d}
endif
