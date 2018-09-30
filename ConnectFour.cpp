// Grupo 23
// Leonardo Santos, Daniel Dong e Jorge Sousa


#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <string.h>
#include <ctime>

//i so vai 0-5
//j so vai 0-6
using namespace std;

vector < vector <char> > board(6,vector<char> (7, '-'));
char type='X';
int memory=0;

map <int, int> point_conv;

int maxi(vector < vector < char> > tableNew, int depth, int limit_depth);
int mini(vector < vector < char> > tableNew, int depth, int limit_depth);

int betamaxi(vector < vector < char> > tableNew, int depth, int limit_depth, int alpha, int beta);
int alphamini(vector < vector < char> > tableNew, int depth, int limit_depth,int alpha, int beta);

void print_board(vector < vector < char > > table)
{
    int i,j;
	
    printf("##################\n");

    for(i=0;i<6;i++)
    {
		
        for(j=0;j<7;j++)
        {
        	if(j==0){
        		printf("# ");
        	}
            cout << table[i][j] << " ";
            if(j==6){
            	printf(" #");
            }
        }	
        cout << "\n";
		
    }

    printf("##################\n");
    printf("  1 2 3 4 5 6 7\n");
    printf("\n");
	
}

int geti(int j, vector < vector < char> > table)
{
    int i=0;
    while(i<5 && table[i+1][j]=='-')
        i++;
    return i;
}

int play(int j)
{
    int i;
    if(board[0][j]!='-' || j <0 || j >6)
	{
        return -1;
    }
	else
    {
        i=geti(j,board);
        if(type == 'X')
            board[i][j]='X';
        else
            board[i][j]='O';
        return i;
    }
}

int horizontalEsq(vector < vector < char > > tableNew, int posi, int posj, char typeNew){
	int j, sum = 0;
	for(j=1;j<4;j++){
		if(posi >= 0 && posi <= 5 && posj-j >= 0 && posj-j <=6){
		//if(posj-j>=0){
			if(tableNew[posi][posj - j] == typeNew){
				sum++;
			}
			else{
				return sum;
			}
		}
		else {
			return sum;
		}
	}
	return sum;
}

int horizontalDir(vector < vector < char > > tableNew, int posi, int posj, char typeNew){

	int j, sum = 0;
	for(j=1;j<4;j++){
		//if(posj+j<=6){
		if(posi >= 0 && posi <= 5 && posj+j >= 0 && posj+j <=6){
			if(tableNew[posi][posj + j] == typeNew){
				sum++;
			}
			else{
				return sum;
			}
		}
		else {
			return sum;
		}
	}
	return sum;
}

int vertCima(vector < vector < char > > tableNew, int posi, int posj, char typeNew){
	int i, sum = 0;
	for(i=1;i<4;i++){
		if(posi-i >= 0 && posi-i <= 5 && posj >= 0 && posj <=6){
		//if(posi-i>=0){
			if(tableNew[posi-i][posj] == typeNew){
				sum++;
			}
			else{
				return sum;
			}
		}
		else {
			return sum;
		}
	}
	return sum;
}

int vertBaixo(vector < vector < char > > tableNew, int posi, int posj, char typeNew){
	int i, sum = 0;
	for(i=1;i<4;i++){
		if(posi+i >= 0 && posi+i <= 5 && posj >= 0 && posj <=6){
		//if(posi+i <= 5){
			if(tableNew[posi+i][posj] == typeNew){
				sum++;
			}
			else{
				return sum;
			}
		}
		else{
			return sum;
		}
	}
	return sum; 
}

int diagEsq(vector < vector < char > > tableNew, int posi, int posj, char typeNew)
{
	int i,sum = 0;
    for(i=1;i<4;i++)
    {
        if(posi+i < 6 && posj-i >= 0)
        {
            if(tableNew[posi+i][posj-i]==typeNew)
                sum++;
            else
                return sum;
        }
        else
            return sum;
    }
    return sum;
}

int diagDir(vector < vector < char > > tableNew, int posi, int posj, char typeNew)
{
	int i,sum = 0;
    for(i=1;i<4;i++)
    {
        if(posi-i >= 0 && posj+i < 7)
        {
            if(tableNew[posi-i][posj+i]==typeNew)
                sum++;
            else
                return sum;
        }
        else
            return sum;
    }
    return sum;
}

int rDiagEsq(vector < vector < char > > tableNew, int posi, int posj, char typeNew)
{
    int i,sum = 0;
    for(i=1;i<4;i++)
    {
        if(posi+i < 6 && posj+i < 7)
        {
            if(tableNew[posi+i][posj+i]==typeNew)
                sum++;
            else
                return sum;
        }
        else
            return sum;
    }
    return sum;
}

int rDiagDir(vector < vector < char > > tableNew, int posi, int posj, char typeNew)
{
    int i,sum = 0;
    for(i=1;i<4;i++)
    {
        if(posi-i >= 0 && posj-i >= 0)
        {
            if(tableNew[posi-i][posj-i]==typeNew)
                sum++;
            else
                return sum;
        }
        else
            return sum;
    }
    return sum;
}

int win(vector < vector < char > > tableNew, int posi, int posj, char typeNew)
{
	int sumHor = horizontalEsq(tableNew, posi, posj, typeNew) + 1 + horizontalDir(tableNew, posi, posj, typeNew);
	int sumVer = vertBaixo(tableNew, posi, posj, typeNew) + 1 + vertCima(tableNew, posi, posj, typeNew);
    int sumDiag = diagEsq(tableNew, posi, posj, typeNew) + 1 + diagDir(tableNew, posi, posj, typeNew);
	int sumRDiag = rDiagEsq(tableNew, posi, posj, typeNew) + 1 + rDiagDir(tableNew, posi, posj, typeNew);
	return max(sumHor, max(sumVer, max(sumDiag, sumRDiag)));
	
}

int hor(vector < vector < char > > tableNew, char typeNew, int posi, int posj){
	int sum = 0,i,j;

	char typeEnemy;

	for(j = posj; j<posj+4;j++){
		if(typeNew == '-')
				typeNew=tableNew[posi][j];
		
		if(typeNew != '-')
		{	
			
			if(typeNew == 'X')
				typeEnemy = 'O';
			else
				typeEnemy = 'X';
		
		
			if(tableNew[posi][j] == typeEnemy){
				return 0;
			}
			else if(tableNew[posi][j] == typeNew){
				sum++;
			}
		}
	}

	if(typeNew == 'X'){
		return -point_conv[sum];
	}
	return point_conv[sum];
}

int countHor(vector < vector < char > > tableNew){
	int i, j, sum = 0;

	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			//if(tableNew[i][j] != '-')	
				sum += hor(tableNew, tableNew[i][j], i, j);				
		}
	}	
	return sum;
}

int vert(vector < vector < char > > tableNew, char typeNew, int posi, int posj){
	int sum = 0,i,j;

	char typeEnemy;
    if(typeNew == 'X')
        typeEnemy = 'O';
    else
        typeEnemy = 'X';




	for(i = posi; i>posi-4;i--){
		if(tableNew[i][posj] == typeEnemy){
			return 0;
		}
		else if(tableNew[i][posj] == typeNew){
			sum++;
		}
	}

	if(typeNew == 'X'){
		return -point_conv[sum];
	}
	return point_conv[sum];
}

int countVert(vector < vector < char > > tableNew){

	int i, j, sum = 0;
	
	for(j=0;j<7;j++){
		for(i=5;i>2;i--){
			if(tableNew[i][j] != '-'){
				sum += vert(tableNew, tableNew[i][j], i, j);
			}
		}
	}

	return sum;
}


int Diag(vector < vector < char> > tableNew, char typeNew, int i, int j)
{
	int k,sum=0;
	char typeEnemy;
	
	for(k=0;k<4;k++)
	{	
		if(typeNew == '-')
			typeNew=tableNew[i-k][j+k];
			
		if(typeNew != '-')
		{	
			
			if(typeNew == 'X')
				typeEnemy = 'O';
			else
				typeEnemy = 'X';
			
			if(tableNew[i-k][j+k] == typeEnemy)
				return 0;
			else if(tableNew[i-k][j+k] == typeNew)
				sum++;
		}
	}

	//cout << "Origem " << i << " " << j << " Sum " << sum << "\n";
	
	if(typeNew == 'X'){
		return -point_conv[sum];
	}
	return point_conv[sum];
}

int countDiag(vector < vector < char> > tableNew)
{	
	int i, j, sum=0;
	
	for(i = 3; i < 6; i++)
	{
		for(j = 0; j < 4; j++)
		{
			sum += Diag(tableNew, tableNew[i][j], i, j);
		}
	}
	
	return sum;
}

int rDiag(vector < vector < char> > tableNew, char typeNew, int i, int j)
{
	int k,sum=0;
	
	char typeEnemy;
	
		
	for(k=0;k<4;k++)
	{
		if(typeNew == '-')
			typeNew=tableNew[i+k][j+k];
		if(typeNew != '-')
		{
			if(typeNew == 'X')
				typeEnemy = 'O';
			else
				typeEnemy = 'X';
			
			if(tableNew[i+k][j+k] == typeEnemy)
				return 0;
			else if(tableNew[i+k][j+k] == typeNew)
				sum++;
		}
	}

	if(typeNew == 'X'){
		return -point_conv[sum];
	}
	return point_conv[sum];
}

int countRDiag(vector < vector < char> > tableNew)
{	
	int i, j, sum=0;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 4; j++)
		{
			sum += rDiag(tableNew, tableNew[i][j], i, j);
		}
	}
	return sum;
}

//vizinhos
queue < vector < vector <char> > > vizinhos(vector < vector < char> > parentBoard, char typePlay)
{
	int i,j;
	
	//cout << "entrei vizinhos\n";
	queue < vector < vector <char> > > vizinho;
	vector < vector <char> > nextChild;
	for(j=0;j<7;j++)
	{
		if(parentBoard[0][j]=='-')
		{
			nextChild=parentBoard;
			i=geti(j,parentBoard);
			nextChild[i][j]=typePlay;
			vizinho.push(nextChild);
		}	
	}
	
	return vizinho;
}

//chamar utility se for o depth maximo
int utility(vector < vector < char> > tableNew){
	return countHor(tableNew) + countVert(tableNew) + countDiag(tableNew) + countRDiag(tableNew);
}

int maxi(vector < vector < char> > tableNew, int depth, int limit_depth)
{	
	memory++;
	if(depth == limit_depth)
		return utility(tableNew);
	
	queue < vector < vector <char> > > vizinho = vizinhos(tableNew, 'O');
	vector < vector <char> > node(6, vector<char>(7));
	int i=0, posi, result, maxValue = -513;

	while(vizinho.size() > 0){

		node = vizinho.front();
		vizinho.pop();
		
		
		while(tableNew[0][i]!='-' && i < 6)
			i++;
		//cout << i <<"\n";
		
		if(node[0][i]=='O')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'O')>=4)
			result = 512;
		else
			result = mini(node,depth+1,limit_depth);
		
		
		
		if(result > maxValue){
			maxValue = result;
		}
		
		//cout <<"max " << depth << " " << result << "\n"; 
		
		if(i<6)
			i++;
	}

	return maxValue;
}

int mini(vector < vector < char> > tableNew, int depth, int limit_depth)
{
	memory++;
	if(depth == limit_depth)
		return utility(tableNew);
	
	queue < vector < vector <char> > > vizinho = vizinhos(tableNew, 'X');
	vector < vector <char> > node(6, vector<char>(7));
	int i=0, posi, result, minValue = 513;
	
	while(vizinho.size() > 0){
		
		node = vizinho.front();
		vizinho.pop();
		
		while(tableNew[0][i]!='-' && i < 6)
			i++;
		
		if(node[0][i]=='X')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'X')>=4)
			result = -512;
		else
			result = maxi(node,depth+1,limit_depth);
		
		if(result < minValue){
			minValue = result;
		}
		
		if(i<6)
			i++;
	}
	
	return minValue;	
}

int minimax(int profundidade){
	queue < vector < vector <char> > > vizinho = vizinhos(board, 'O');
	vector < vector <char> > node(6, vector<char>(7)); 
	int pos, posi, i=0,result, maxValue = -513;
	memory++;
	while(vizinho.size() > 0){

		node = vizinho.front();
		vizinho.pop();
		
		while(board[0][i]!='-' && i < 6)
			i++;
		
		if(node[0][i]=='O')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'O')>=4)
			result = 512;
		else
			result = mini(node,1, profundidade);
		
		cout << "Result = " << result << ", Column = " << i+1 << "\n";
		
		if(result > maxValue){
			maxValue = result;
			pos=i;
		}
		if(i<6)
			i++;	
	}
	printf("\n");
	printf("Jogador O escolheu a coluna %d\n", pos+1);
	return pos;
}

//alpha beta
int betamaxi(vector < vector < char> > tableNew, int depth, int limit_depth, int alpha, int beta)
{	
	memory++;
	if(depth == limit_depth)
		return utility(tableNew);
	
	queue < vector < vector <char> > > vizinho = vizinhos(tableNew, 'O');
	vector < vector <char> > node(6, vector<char>(7));
	int i=0, posi, result, maxValue = -513;

	while(vizinho.size() > 0){

		node = vizinho.front();
		vizinho.pop();
		
		while(tableNew[0][i]!='-' && i < 6)
			i++;
		
		if(node[0][i]=='O')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'O')>=4)
			result = 512;
		else
			result = alphamini(node,depth+1,limit_depth, alpha, beta);
		
		
		
		if(result > maxValue){
			maxValue = result;
		}
		
		if(result >= beta)
			return result;
		
		alpha = max(alpha,result);
		
		if(i<6)
			i++;
	}

	return maxValue;
}

int alphamini(vector < vector < char> > tableNew, int depth, int limit_depth,int alpha, int beta)
{
	memory++;
	if(depth == limit_depth)
		return utility(tableNew);
	
	queue < vector < vector <char> > > vizinho = vizinhos(tableNew, 'X');
	vector < vector <char> > node(6, vector<char>(7));
	int i=0, posi, result, minValue = 513;
	
	while(vizinho.size() > 0){
		
		node = vizinho.front();
		vizinho.pop();
		
		while(tableNew[0][i]!='-' && i < 6)
			i++;
		
		if(node[0][i]=='X')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'X')>=4)
			result = -512;
		else
		{
			result = betamaxi(node,depth+1,limit_depth, alpha, beta);
		}
		
		if(result < minValue){
			minValue = result;
		}


		
		if(result <= alpha)
			return result;
		
		beta = min(beta,result);
		
		if(i<6)
			i++;
	}
	
	return minValue;	
}

int alphabeta(int alpha, int beta, int profundidade){
	queue < vector < vector <char> > > vizinho = vizinhos(board, 'O');
	vector < vector <char> > node(6, vector<char>(7)); 
	int pos, posi, i=0,result, maxValue = -513;
	memory++;
	while(vizinho.size() > 0){

		node = vizinho.front();
		vizinho.pop();
		
		while(board[0][i]!='-' && i < 6)
			i++;
		
		if(node[0][i]=='O')
			posi = 0;
		else
			posi=geti(i,node)+1;
		
		if(win(node, posi, i,'O')>=4)
			result = 512;
		else
			result = alphamini(node,1,profundidade, alpha, beta);
		
		
		
		if(result > maxValue){
			maxValue = result;
			pos=i;
		}

		cout << "Result = " << result << ", Column = " << i+1 << "\n";
		
		if(result >= beta)
			return pos;
		
		alpha = max(alpha,result);
		
		if(i<6)
			i++;	
	}
	printf("\n");
	printf("Jogador O escolheu a coluna %d\n", pos+1);
	return pos;
}

int main()
{
	
    int pos,i,posi=1;
    int profundidade, algoritmo, opcao;

    clock_t start;
    double duration;

    printf("Qual algoritmo que deseja que seja utilizado?\n");
    printf("1-Minimax\n");
    printf("2-AlfaBeta\n");
    scanf("%d", &algoritmo);
    while(algoritmo!=1 && algoritmo !=2){
    	printf("Escolha nao valida.\n");
    	printf("Deve escolher entre 1 (minimax) e 2 (alfabeta)\n");
    	scanf("%d", &algoritmo);
    }
    printf("Qual a profundidade desejada?\n");
    if(algoritmo == 1){
    	printf("1 (Muito facil) até 6 (Dificil)\n");
	}
	else{
		printf("1 (Muito Facil) até 8 (Dificil)\n");
	}
	

	scanf("%d", &profundidade);
	while((profundidade < 1 || profundidade > 6) && algoritmo == 1){
		printf("Profundidade nao valida.\n");
		printf("Escolha valores entre 1 e 6\n");
		scanf("%d", &profundidade);
	}

	while((profundidade < 1 || profundidade > 8) && algoritmo == 2){
		printf("Profundidade nao valida.\n");
		printf("Escolha valores entre 1 e 8\n");
		scanf("%d", &profundidade);
	}

	printf("\n");

	printf("Gostaria de começar jogando?\n");
	printf("1-Sim\n");
	printf("2-Não\n");
	scanf("%d", &opcao);

	while(opcao != 1 && opcao != 2){
		printf("Opcão nao Valida\n");
		printf("Gostaria de começar jogando?\n");
		scanf("%d", &opcao);
	}
	if(opcao==1)
		type='X';
	else
		type='O';	

    print_board(board);

	//conversao de numero de pecas em linha para pontos
	point_conv[0]=0;
	point_conv[1]=1;
	point_conv[2]=10;
	point_conv[3]=50;


	
    for(i=0;i<42;i++)
    {
        if(type == 'X'){
			
	        cout << "Insira Coluna: ";
	        cin >> pos;
	        while((posi=play(pos-1))==-1){
	            cout << "Coluna nao valida, insira outra: ";
	            cin >> pos;
	        }
			//cout << pos << " " << posi << "\n";
			pos--;
			
			if(win(board, posi,pos,type) >= 4)
			{
				cout << "\nO JOGADOR X GANHOU!\n";
				print_board(board);
				return 0;
			}
			
		}
		else{
			memory = 0;
			start = clock();
			if(algoritmo == 1){
				
				pos=minimax(profundidade);
				posi = play(pos);
  			}
  			if(algoritmo == 2) {
  				pos=alphabeta(-513, 513, profundidade);
    			posi = play(pos);
  			}
			
			duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
			cout << "Tempo: " << duration << " segundos\n" ;
			cout << "Memoria: " << memory << "\n";
			
			if(win(board, posi,pos,type) >= 4)
			{
				cout << "\nO JOGADOR O GANHOU!\n";
				print_board(board);
				return 0;
			}
			
		}
		
		cout<<"\n\n";
		
        print_board(board);

		
        if(type == 'O')
            type = 'X';
        else
            type = 'O';
    }

    printf("O jogo empatou!\n");

	print_board(board);
	
    return 0;
}
