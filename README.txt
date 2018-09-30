----------------------------------------------------------English

AI project made by Leonardo Santos and Daniel Dong

Instructions:

To compile the program:

$ g++ 16_puzzle_solver.cpp

To run the program:

-With DFS:
$ ./a.out -dfs

-With BFS:
$ ./a.out -bfs

-DFSI (iterative DFS):
$ ./a.out -dfsi

-Greedy:
	-Using Manhattan distance heuristic:
		$ ./a.out -g -m
	-Using misplaced pieces heuristics:
		$ ./a.out -g -f 

-A*:
	-Using Manhattan distance heuristics:
		$ ./a.out -astar -m
	-Using misplaced pieces heuristics:	
		$ ./a.out -astar -f


INPUT: An inicial 4x4 Board configuration and a final(objective) 4x4 configuration :

Example:

1 2 3 4 
5 6 7 8
9 10 11 12
13 14 15 0

1 2 0 3 
4 5 6 7 
8 9 10 11
12 13 14 15


-------------------------------------------------------------------------------------PT-BR

Projeto de IA feito por Leonardo Santos e Daniel Dong

Para compilar o programa, basta escrever no terminal:

$ g++ 16_puzzle_solver.cpp

Para rodar o programa:

-DFS(busca em profundidade): 
$ ./a.out -dfs

-BFS(busca em largura):
$ ./a.out -bfs

-DFSI (busca em profundidade iterativa):
$ ./a.out -dfsi

-Gulosa:
	-Usando a heurística Manhattan distance:
		$ ./a.out -g -m
	-Usando a heurística de número de peças fora do lugar:
		$ ./a.out -g -f 

-A*:
	-Usando a heurística Manhattan distance:
		$ ./a.out -astar -m
	-Usando a heurística de número de peças fora do lugar:	
		$ ./a.out -astar -f




