#ifndef _MATRICE_H_
#define _MATRICE_H_

#include <stdlib.h>

class matrice
{
	private:
		int dim1,dim2;
		int ** mat;
	public:
		matrice() {dim1=0;dim2=2;mat=NULL;};
		~matrice();

		int & get_dim1() {return dim1;};
		int & get_dim2() {return dim2;};
		int & get_case(int d1,int d2) {return mat[d1][d2];};

		void add(int,int);

};




#endif