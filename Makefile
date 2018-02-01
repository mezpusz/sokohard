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

CLASSES = filewriter inputparser levelgenerator main map mapgenerator pattern state
SRCS = $(addprefix src/, $(addsuffix .cpp, $(CLASSES)))
OBJS = $(addprefix out/, $(addsuffix .o, $(CLASSES)))

.PHONY: depend clean sokohard

all:    out/sokohard out

out/sokohard: out $(OBJS)
		$(CXX) $(CFLAGS) $(INCLUDES) -o out/sokohard $(OBJS)

out:
		mkdir out

out/%.o: src/%.cpp
		$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(RM) -r out/

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
