#include <stdio.h>
#include <iostream>
#include <ctime>

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int r,n,k,s;
	printf("¬ведите количество вершин- ");
	scanf("%d",&n);
	printf("¬ведите исходную вершину- ");
	scanf("%d",&s);
	printf("¬ведите веро€тность заполнени€ ненулевых элементов 1 к ");
	scanf("%d",&k);
	int** C = new int*[n];
	for(int i = 0; i < n; i++)
		C[i] = new int[n];
	for(int i = 0; i < n; i++)
		C[i][i] = 0;
	for(int i = 0; i < n; i++)
		for(int j = i+1;j < n; j++)
		{
			r = rand()%k;
			if(!r)
				C[i][j] = C[j][i] = rand()%9+1;
			else
				C[i][j] = C[j][i] = 0;
		}
	FILE* f = fopen("input.txt","w");
	fprintf(f, "%d %d\n",n,s);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		{	
			fprintf(f,"%d ",C[i][j]);
			if(j == n-1)
				fprintf(f,"\n");
			else
				fprintf(f," ");
		}
	for(int i = n-1; i >= 0; i--)
		delete [] C[i];
	return 0;
}
