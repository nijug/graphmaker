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
		@./a.out -f Tgraf.txt -k 1 9 11 > output.txt
		@diff output.txt Tcorrect.txt
test2:
		@./a.out ./a.out -f Tgraf2.txt -k 0 999 848 56 178 > output.txt
		@diff output.txt Tcorrect2.txt
test3:
		@./a.out -f Tgraf3.txt -k 0 1 2 > output.txt
		@diff output.txt Tcorrect3.txt

test:	test1 test2 test3


