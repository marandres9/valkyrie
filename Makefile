SRC=src
#  linked list class (C)
ITEMLISTSRC=src/stockControl

CPP_SOURCES := $(wildcard $(SRC)/*.cpp)
C_SOURCES := $(wildcard $(ITEMLISTSRC)/*.c)

OBJECTS := $(patsubst $(SRC)/%.cpp, %.o, $(CPP_SOURCES)) $(patsubst $(ITEMLISTSRC)/%.c, %.o, $(C_SOURCES))

CPPFLAGS=-Wall
CFLAGS=-Wall

# all:
# 	echo $(DEPS)

application: $(OBJECTS)
	g++ $(CFLAGS) $(shell ${WXWIDGETS_WXCONFIG} --libs) $(OBJECTS) -o $@

%.o: $(SRC)/%.cpp
	g++ $(CPPFLAGS) $(shell ${WXWIDGETS_WXCONFIG} --cppflags) -c $< -o $@

%.o: $(ITEMLISTSRC)/%.c
	gcc $(CFLAGS) -c $< -o $@
	
clean:
	rm *.o
# $< = The name of the first prerequisite. 
# $^ = The names of all the prerequisites,
# $@ = The file name of the target of the rule.