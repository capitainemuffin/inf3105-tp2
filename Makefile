options = -pedantic -Wall -std=c++11
programme = tp2

.PHONY : clean

default : $(programme)

debug : main.o arbremap.o	
	g++ -D debug -o $(programme) main.o arbremap.o $(options)
	./$(programme)
	@make clean

$(programme) : main.o arbremap.o
	g++ -o $(programme) main.o arbremap.o $(options)

main.o : main.cpp
	g++ -c -o main.o main.cpp $(options)

arbremap.o : arbremap.cpp pile.h
	g++ -c -o arbremap.o arbremap.cpp $(options)

clean : 
	@rm -f $(programme)
	@rm -f *.o
	@rm -fr tests