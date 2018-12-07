///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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