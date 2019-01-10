

.PHONY: clean round

SOURCES = thing.cpp lexer.cpp parser.cpp main.cpp
HEADERS = thing.hpp lexer.hpp parser.cpp
OBJ = $(patsubst %.cpp,%.o,$(SOURCES)) 


%.o: %.cpp *.hpp
	g++ -pipe -c -o $@ $<

teste: $(OBJ)
	g++ *.o -o teste

clean:
	rm -f *.o
	rm -f teste
	
roud: teste clean
