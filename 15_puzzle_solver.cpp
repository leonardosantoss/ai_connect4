#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <ctime>
#include <string.h>
#include <utility>

using namespace std;

map <vector<vector <int> >, int > visited;
map <vector<vector <int> >, vector<vector <int> > > parent;
map <vector<vector <int> > , int > dist;
int fim_depth = -1;
unsigned int max_node = 0;

int solve(int solvability[], int pos){

	int i,k;
	int inversoes;

	inversoes = 0;
	for(i=0;i<16;i++){
		k=i;
		while(k<16){
			if(solvability[i] > solvability[k] && solvability[k] != 0){
				inversoes++;
			}
			k++;
		}
	}

	if((pos<4 || pos==8 || pos == 9 || pos == 10 || pos == 11) && inversoes%2 == 0){
		//printf("Não possui solução\n");
		return 0;
	}
	else if((pos<=7 && pos>=4 || pos>=12) && inversoes%2 != 0){
		//printf("Não possui solução\n");
		return 0;
	}
	else {
		//printf("Possui solução\n");
		return 1;
	}

}

vector < vector <int> > swap(vector < vector <int> > inicio, int x, int y, int xa, int ya)
{
	vector < vector <int> > alterado(inicio);
	
	alterado[x][y]=inicio[xa][ya];
	alterado[xa][ya]=0;
	
	return alterado;
}

vector < vector < vector <int> > > vizinhos(vector < vector < int > > inicio)
{
	vector<vector < vector < int > > > vizinho;
	vector < vector < int > > alterado(4, vector<int> (4));
	int linha,coluna,i,j,l,k;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(inicio[i][j]==0)
			{
				linha=i;
				coluna=j;
				break;
			}
		}
	
	for(k=-1;k<=1;k++)
	{
		for(l=-1;l<=1;l++)
		{
			//cout << "k" << k << " j" << j << "\n";
			if((k||l) && ((k!=l) && (k!=l*-1)))
			{
				//cout << "-----\n\n";
				if(linha+k>=0 && linha+k<4 && coluna+l>=0 && coluna+l<4)
				{
					alterado=swap(inicio,linha,coluna,linha+k,coluna+l);
					if(visited[alterado]!=1)	
						vizinho.push_back(alterado);
				}
			}
		}
	}
	
	return vizinho;
}

int dfs(vector < vector < int > > inicio, vector < vector < int > > fim, int depth, int limit)
{
	if(visited.size()>max_node)
		max_node = visited.size();
	
	
	if(inicio==fim)
	{
		return 1;
	}
	
	if(limit<depth)
	{
		return 0;
	}
	vector < vector < vector <int> > > vizinho = vizinhos(inicio);
	vector < vector < vector <int> > >::iterator it;
	vector < vector <int> > temp;
	
	for(it=vizinho.begin() ; it!=vizinho.end() ; it++)
	{	

		temp = *it;
		visited.insert(make_pair(temp,1));
		parent.insert(make_pair(temp,inicio));
		if(dfs(temp,fim,depth+1,limit))
		{
			return 1;
		}
	}
	return 0;
}

int dfsi(vector < vector < int > > inicio, vector < vector < int > > fim)
{
	int depth=0;
	while(!dfs(inicio,fim,0,depth))
	{	
		parent.clear();
		visited.clear();
		depth++;
		if(depth==30)//LIMITE MAXIMO DO DFSI para o caso de nao encontrar solucoes e terminar
			return 0;
	}
	
	return 1;
}

int bfs(vector < vector < int > > inicio, vector < vector < int > > fim)
{
	queue < vector < vector <int> > > Q;
	
	Q.push(inicio);
	
	vector < vector < vector <int> > > vizinho;
	vector < vector < vector <int> > >::iterator it;
	vector < vector <int> > temp;
	vector < vector <int> > node;
	
	while(Q.size()!=0)
	{
		if(visited.size()>max_node)
			max_node = visited.size();
		
		vizinho.clear();
		
		node = Q.front();
		Q.pop();
		
		vizinho = vizinhos(node);
		
		if(node == fim)
			return 1;
		
		for(it=vizinho.begin() ; it!=vizinho.end() ; it++)
		{	
			temp = *it;
			visited.insert(make_pair(temp,1));
			parent.insert(make_pair(temp,node));
			Q.push(temp);
		}	
	}
	
	return 0;
}

void print_path(vector < vector < int > > node, vector < vector < int > > inicio)
{
	int i,j;
	
	if(node != inicio)	
		print_path(parent[node],inicio);
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			cout << node[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	
	fim_depth++;	
}

int manhattan(vector < vector < int > > inicio, vector < vector < int > > fim)
{
	int dist=0, i,j,k,t;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(inicio[i][j]!=0){
				for(k=0;k<4;k++){
					for(t=0;t<4;t++){
						if(inicio[i][j]==fim[k][t])
							dist+=abs(i-k)+abs(j-t);
					}
				}
			}
		}
	}
	
	return dist;
}

int foraLugar(vector < vector < int > > inicio, vector < vector < int > > fim){

	int pecas = 0;
	int i,j;	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(inicio[i][j] != fim[i][j]){
				pecas++;
			}
		}
	}
	return pecas;
}

priority_queue < pair < int, vector < vector <int> > > >vizinhos_segundo(vector < vector < int > > inicio, vector < vector < int > > fim, int seletor)
{
	if(visited.size()>max_node)
		max_node = visited.size();
	
	priority_queue < pair < int, vector < vector <int> > > > vizinho;
	vector < vector < int > > alterado(4, vector<int> (4));
	pair <int, vector < vector < int > > > par;
	int linha,coluna,i,j,l,k, dist;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(inicio[i][j]==0)
			{
				linha=i;
				coluna=j;
				break;
			}
		}
	
	for(k=-1;k<=1;k++)
	{
		for(l=-1;l<=1;l++)
		{
			
			if((k||l) && ((k!=l) && (k!=l*-1)))
			{
				
				if(linha+k>=0 && linha+k<4 && coluna+l>=0 && coluna+l<4)
				{
					alterado=swap(inicio,linha,coluna,linha+k,coluna+l);
					if(seletor == 0){
						dist = manhattan(alterado, fim);
					}
					else if(seletor == 1){
						dist = foraLugar(alterado, fim);
					}
					par = make_pair(-dist,alterado);
					if(visited[alterado]!=1)	
						vizinho.push(par);
				}
			}
		}
	}
	
	return vizinho;
}




int greedy(vector < vector < int > > inicio, vector < vector < int > > fim, int depth, int limit, int seletor){

	if(visited.size()>max_node)
		max_node = visited.size();

	pair <int, vector < vector < int > > > par;

	if(inicio==fim)
	{
		return 1;
	}
	
	if(limit<depth)
	{
		return 0;
	}
	priority_queue < pair < int, vector < vector <int> > > > vizinho = vizinhos_segundo(inicio, fim, seletor);
	vector < vector <int> > temp;
	

	while(vizinho.size() != 0){
		par = vizinho.top();
		temp = par.second;
		vizinho.pop();
		visited.insert(make_pair(temp, 1));
		parent.insert(make_pair(temp, inicio));
		if(greedy(temp,fim, depth+1, limit, seletor)){
			return 1;
		}

	}

	

	return 0;
}



priority_queue < pair <int, pair < vector < vector < int > > , int > > >vizinhos_terceiro(vector < vector < int > > inicio, vector < vector < int > > fim, int seletor, int profundidade)
{
	if(parent.size()>max_node)
		max_node = parent.size();
	
	priority_queue < pair < int, pair < vector < vector <int> > , int > > > vizinho;
	vector < vector < int > > alterado(4, vector<int> (4));
	pair <int, pair < vector < vector < int > > , int > > par;
	int linha,coluna,i,j,l,k, dist;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(inicio[i][j]==0)
			{
				linha=i;
				coluna=j;
				break;
			}
		}
	
	for(k=-1;k<=1;k++)
	{
		for(l=-1;l<=1;l++)
		{
			
			if((k||l) && ((k!=l) && (k!=l*-1)))
			{
				
				if(linha+k>=0 && linha+k<4 && coluna+l>=0 && coluna+l<4)
				{
					alterado=swap(inicio,linha,coluna,linha+k,coluna+l);
					if(seletor == 0){
						dist = manhattan(alterado, fim);
					}
					else if(seletor == 1){
						dist = foraLugar(alterado, fim);
					}
					par = make_pair(-dist,make_pair(alterado, profundidade+1));
					//if(visited[alterado]!=1)	
						vizinho.push(par);
				}
			}
		}
	}
	
	return vizinho;
}


int astar(vector < vector < int > > inicio, vector < vector < int > > fim, int seletor){

	pair <int, pair < vector < vector < int > > , int > > par;
    priority_queue < pair <int, pair < vector < vector < int > > , int > > > vizinho = vizinhos_terceiro(inicio, fim, seletor, 0);
    int profundidade = 1;
    vector < vector <int> > temp;
    pair <int, pair < vector < vector < int > > , int > > node;
    priority_queue < pair <int, pair < vector < vector < int > > , int > > > Q;
    int temp_heuristic, tentative_gScore;

    Q.push(make_pair(0,make_pair(inicio,0)));

    while(Q.size() != 0){
        node = Q.top();
        Q.pop();
        if(node.second.first == fim){
            return 1;
        }

        vizinho = vizinhos_terceiro(node.second.first,fim,seletor, node.second.second+1);

        while(vizinho.size() != 0){

            /*par = vizinho.top();
            temp_heuristic =  par.first;
            temp = par.second;
            vizinho.pop();
            visited.insert(make_pair(temp, 1));
            parent.insert(make_pair(temp, node.second.first));
            Q.push(make_pair(temp_heuristic,temp));
			*/

			par = vizinho.top();
            temp_heuristic =  par.first;
            temp = par.second.first;
           	profundidade=par.second.second;

            vizinho.pop();
           // visited.insert(make_pair(temp, 1));
            dist.insert(make_pair(temp,-100000));

            tentative_gScore = temp_heuristic - profundidade;

            if(tentative_gScore >= dist[temp]){
            	parent.insert(make_pair(temp, node.second.first));
            	dist[temp] = tentative_gScore;
            	Q.push(make_pair(tentative_gScore,make_pair(temp, profundidade)));
            }
        }

    }
    return 0;
}




int main(int argc, char **argv)
{
	int i,j,inicio_v[16],count=0,valor,pos,result;
	vector < vector < int > > inicio(4, vector<int> (4)),fim(4, vector<int> (4));
	clock_t start;
	double duration;
	
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			cin >> valor;
			inicio[i][j]=valor;
			inicio_v[count]=valor;
			if(valor==0)
				pos=count;
			count++;
		}
		
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			cin >> fim[i][j];
		}
	
	if(solve(inicio_v, pos))
	{


		visited.insert(make_pair(inicio,1));
		start = clock();
		
		if(strcmp(argv[1], "-dfs" ) == 0){
			result = dfs(inicio,fim,0,15);  //DFS
		}
		else if(strcmp(argv[1], "-dfsi" ) == 0){
			result = dfsi(inicio,fim);      //DFSI
		}
		else if(strcmp(argv[1], "-bfs" ) == 0){
			result = bfs(inicio,fim);      //BFS
		}
		else if(strcmp(argv[1], "-g") == 0){

			if(strcmp(argv[2], "-m") == 0){
				result = greedy(inicio, fim,0,20, 0);
			}
			else if(strcmp(argv[2], "-f") == 0){
				result = greedy(inicio, fim,0,20, 1);
			}
		}
		else if(strcmp(argv[1], "-astar") == 0){
				if(strcmp(argv[2], "-m") == 0){
					result = astar(inicio, fim, 0);
				}
				else if(strcmp(argv[2], "-f") == 0){
					result = astar(inicio, fim , 1);
				}
		}
		
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		if(result)
		{
			print_path(fim,inicio);
			cout << "Profundidade: " << fim_depth << "\n";
			cout << "Memoria: " << max_node << " nodos visitados\n";
			cout << "Tempo: " << duration << " segundos\n";
		}
		else
			cout << "NAO ENCONTROU CAMINHO\n";
		
		visited.clear();
		parent.clear();
	}
	else
	{
		cout << "NAO TEM SOLUCAO";
	}
	return 0;
}