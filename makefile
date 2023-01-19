# all: graph

# graph: main.c graph.c graph.h
# 	gcc -Wall -g -o graph main.c graph.c

# clean:
# 	rm -rf graph

all: graph

graph: main.c graph.c graph.h
	gcc -Wall -g -o graph main.c graph.c

clean:
	rm -rf graph