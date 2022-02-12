# path to wx-config
# example: WX_CONFIG=/home/user/wxWidgets-X.X.X/gtk-build/wx-config
WX_CONFIG=${WXWIDGETS_WXCONFIG}

CC=gcc
CCPP=g++

SRC=src
#  linked list class (C)
LINKEDLISTSRC=src/linkedList

CPP_SOURCES := $(wildcard $(SRC)/*.cpp)
C_SOURCES := $(wildcard $(LINKEDLISTSRC)/*.c)

OBJECTS := $(patsubst $(SRC)/%.cpp, %.o, $(CPP_SOURCES)) $(patsubst $(LINKEDLISTSRC)/%.c, %.o, $(C_SOURCES))

CPPFLAGS=-Wall
CFLAGS=-Wall

# all:
# 	echo $(DEPS)

valkyrie: $(OBJECTS)
	$(CCPP) $(CFLAGS) $(OBJECTS) $(shell $(WX_CONFIG) --libs) -o $@

%.o: $(SRC)/%.cpp
	$(CCPP) $(CPPFLAGS) $(shell $(WX_CONFIG) --cppflags) -c $< -o $@

%.o: $(LINKEDLISTSRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm *.o
# $< = The name of the first prerequisite. 
# $^ = The names of all the prerequisites,
# $@ = The file name of the target of the rule.