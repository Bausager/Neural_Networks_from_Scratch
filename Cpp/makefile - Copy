
# Directories
# Include folder for header files
IDIR = ./include
# Source folder for .cpp files
SDIR = ./src
# Object folder for .o files
ODIR = ./obj
# Library folder (if applicable)
LDIR = ./lib

# Compiler and flags
CC = g++
#CFLAGS = -I$(IDIR) -Wall -std=c++14
CFLAGS = -I$(IDIR) -Wall -std=c++14

LIBS = -lm               # Libraries to link with (math library in this case)

# Dependencies and object files
_DEPS = numerics.h layers.h activation.h data_gen.h loss.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o numerics.o layers.o activation.o data_gen.o loss.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Rule for compiling .cpp files into .o object files
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Target for creating the executable
output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Clean target to remove object files and other generated files
.PHONY: clean


clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~