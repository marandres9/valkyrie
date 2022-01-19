CC=gcc
CCPP=g++
SRC=src
#  linked list class (C)
LINKEDLISTSTC=src/linkedList

# path to: wx-config
WX_CONFIG=${WXWIDGETS_WXCONFIG}

CPP_SOURCES := $(wildcard $(SRC)/*.cpp)
C_SOURCES := $(wildcard $(LINKEDLISTSTC)/*.c)

OBJECTS := $(patsubst $(SRC)/%.cpp, %.o, $(CPP_SOURCES)) $(patsubst $(LINKEDLISTSTC)/%.c, %.o, $(C_SOURCES))

CPPFLAGS=-Wall
CFLAGS=-Wall

# all:
# 	echo $(DEPS)

application: $(OBJECTS)
	$(CCPP) $(CFLAGS) $(shell $(WX_CONFIG) --libs) $(OBJECTS) -o $@

%.o: $(SRC)/%.cpp
	$(CCPP) $(CPPFLAGS) $(shell $(WX_CONFIG) --cppflags) -c $< -o $@

%.o: $(LINKEDLISTSTC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm *.o
# $< = The name of the first prerequisite. 
# $^ = The names of all the prerequisites,
# $@ = The file name of the target of the rule.