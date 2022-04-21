a.out: main.o dijkstra.o bfs.o graph.o utilities.o
			$(CC) -Wall -pedantic -O3 $^

main.o: graph.o utilities.o bfs.o dijkstra.o
dijkstra.o: dijkstra.h graph.o bfs.o utilities.o
bfs.o: bfs.h graph.o utilities.o
graph.o: graph.h utilities.o
utilities.o: utilities.h



.PHONY: clean test1 test2 test3 test

clean:
		-rm *.o a.out
test1:
		@./a.out -f tests/Tgraf.txt -k 1 9 11 > tests/output.txt
		@diff tests/output.txt tests/Tcorrect.txt
test2:
		@ ./a.out -f tests/Tgraf2.txt -k 5 999 8 30 > tests/output.txt
		@diff tests/output.txt tests/Tcorrect2.txt
test3:
		@./a.out -f tests/Tgraf3.txt -k 0 1 2 3 4 5 6 7 8 > tests/output.txt
		@diff tests/output.txt tests/Tcorrect3.txt

test:	test1 test2 test3


