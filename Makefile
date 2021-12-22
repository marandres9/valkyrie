PROGRAM=main

ITEMLIST=itemList
ITEMLISTSRC=stockControl

LISTSORTING=listSorting
SRC=src

OBJECTS=$(PROGRAM).o $(ITEMLIST).o $(LISTSORTING).o

CPPFLAGS=-Wall
CFLAGS=-Wall

$(PROGRAM): $(OBJECTS)
	g++ $(CFLAGS) $(shell ${WXWIDGETS_WXCONFIG} --libs) $^ -o $@

%.o: $(SRC)/%.cpp
	g++ $(CPPFLAGS) $(shell ${WXWIDGETS_WXCONFIG} --cppflags) -c $< -o $@

%.o: $(SRC)/$(ITEMLISTSRC)/%.c
	gcc $(CFLAGS) -c $< -o $@
	
clean:
	rm *.o $(PROGRAM)
# $< = The name of the first prerequisite. 
# $^ = The names of all the prerequisites,
# $@ = The file name of the target of the rule.