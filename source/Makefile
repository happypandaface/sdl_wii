# This makefile checks date modified! and the comments explain why

SOURCEDIR = ../source/
INC_DIR1 = ../source/include/
INC_DIR2 = ../source/include/images/
INC_DIR3 = ../source/include/levels/
# I found this code on SO it gets all the files in a directory given a searcher, pretty nifty
SRCS := $(shell find $(SOURCEDIR) -name '*.cpp')
INCS := $(shell find $(INC_DIR1) -name '*.h')
INCS := $(shell find $(INC_DIR2) -name '*.h')
INCS := $(shell find $(INC_DIR3) -name '*.h')
# this takes a variable and goes through and replaces a string with another, in this case
# it's replacing '.cpp' with '.o'
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -L../lib -I../source/include -I../source/wininclude -lmingw32 -lSDLmain -lSDL -lSDL_image -DWINDOWS_BUILD -DDEBUG_BUILD -Wall

all: program

# this makes program dependant on $(OBJS), and auto does modified checks
program: $(OBJS) $(INCS)
	g++ -g $^ -o ../winbuild/main $(CFLAGS)
# I guess the $^ referrs to the $(OBJS)

.cpp.o:
	g++ -Wall -c $^ $(CFLAGS)

#I don't really get how any of this works actually, but it's great.