#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fstream>
#include <omp.h>
int main()
{
	setlocale(LC_ALL, "Russian");
	int p = 0;
	double t1, t2;
	FILE* fin = fopen("input.txt","r");
	if (!fin)
	{
		printf("файл с исходными данными не найден\n");
		getchar();
		return 1;
	}
	fscanf(fin,"%d",&p);
	int** C = new int*[p];
	for (int i = 0; i < p; i++)
		C[i] = new int[p];
	int* H = new int[p];
	int s;
	fscanf(fin,"%d",&s);
	for (int i = 0; i < p; i++)
		for (int j = 0; j < p; j++)
			fscanf(fin,"%d",&C[i][j]);
	fclose(fin);
	int *Distance = new int[p], j, v;
	bool *Visited = new bool[p];
	for (int i = 0; i < p; i++)
	{
		Distance[i] = INT_MAX;
		Visited[i] = false;
	}
	H[s-1] = 0;
	Distance[s-1] = 0;
	Visited[s-1] = true;
	v = s-1;
	t1 = omp_get_wtime();
	for (j = 0; j < p-1; j++)
	{
		if(Distance[v] != INT_MAX) 
			for (int u = 0; u < p; u++)
				if (!Visited[u] && C[v][u] && Distance[u] > Distance[v] + C[v][u])
				{
					Distance[u] = Distance[v] + C[v][u];
					H[u] = v+1;
				}
		int m = INT_MAX;
		v = -1;
		for (int u = 0; u < p; u++)
			if (!Visited[u] && Distance[u] < m)
			{
				v = u;
				m = Distance[u]; 
			}
		if(v == -1)
break;
		Visited[v] = true;
	}
	t2 = omp_get_wtime();
	int* Route = new int[p]; 
	FILE* fout = fopen("output.txt","w");
	fprintf(fout,"Длинна пути из начальной вершины до остальных:\t\n");
	for (int i = 0; i < p; i++) 
		if (Distance[i] != INT_MAX)
		{
			int l = i+1, k;
			Route[0] = l;
			for(k = 1; l != s; k++)
				Route[k] = l = H[l-1];
			fprintf(fout,"%d > %d = %d\n",s,i+1,Distance[i]);
			fprintf(fout,"путь:");
				for(int i = k-1; i >= 0; i--)
					fprintf(fout," %d",Route[i]);
				fprintf(fout,"\n");
		}
	else
		fprintf(fout,"%d > %d = маршрут недоступен\n",s,i+1);
	fprintf(fout,"Время работы алгоритма: %f",t2-t1);
	fclose(fout);
	delete []Distance;
	delete []Visited;
	delete []H;
	delete []Route;
	for(int i = p-1; i>=0; i--)
		delete [] C[i];
	return 0;
}
