# Definir linkTarget
linkTarget = run

# Definir as bibliotecas a serem utilizadas
LIBS = -lSDL2

# Definir as flags.
# CFLAGS = -std=c++17 -pg
CFLAGS = -std=c++17 -Ofast

# Define the object files that we need to use.
objects = main.o \
				$(patsubst %.cpp,%.o,$(wildcard ./Source/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard ./Triangulation/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard ./Visualization/*.cpp)) \
				$(patsubst %.cpp,%.o,$(wildcard ./Sorts/*.cpp))
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)