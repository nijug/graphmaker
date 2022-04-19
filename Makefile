a.out: main.o dijkstra.o bfs.o graph.o utilities.o
			$(CC) -Wall -pedantic -O3 $^

main.o: graph.o utilities.o bfs.o dijkstra.o
dijkstra.o: dijkstra.h graph.o bfs.o utilities.o
bfs.o: bfs.h graph.o utilities.o
graph.o: graph.h utilities.o
utilities.o: utilities.h



.PHONY: clean

clean:
		-rm *.o a.out
