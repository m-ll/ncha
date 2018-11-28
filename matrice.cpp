#include "matrice.h"

matrice::~matrice()
{
	for(int i=0;i<dim1;i++)
	{
		delete[] mat[i];
		mat[i]=NULL;
	}
	delete[] mat;
	mat=NULL;
}

void matrice::add(int c1,int c2)
{
	dim1++;
	mat=(int **)realloc(mat,dim1*sizeof(int *));
	mat[dim1-1]=new int[dim2];
	mat[dim1-1][0]=c1;
	mat[dim1-1][1]=c2;
}