///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

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