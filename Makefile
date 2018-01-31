#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'sokohard'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CXX = clang++

# define any compile-time flags
CFLAGS = -Wall -O3 -std=c++17 -stdlib=libc++

# define any directories containing header files other than /usr/include
INCLUDES = -I.

# define the CXX source files
SRCS = FileWriter.cpp InputParser.cpp LevelGenerator.cpp Main.cpp Map.cpp MapGenerator.cpp Pattern.cpp State.cpp

# define the CXX object files 
OBJS = $(addprefix out/, $(SRCS:.cpp=.o))

.PHONY: depend clean sokohard

all:    out/sokohard out

out/sokohard: out $(OBJS)
		$(CXX) $(CFLAGS) $(INCLUDES) -o out/sokohard $(OBJS)

out:
		mkdir out

out/%.o: %.cpp
		$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(RM) -r out/

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
