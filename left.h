///
/// Copyright (c) 2002-19 m-ll. All Rights Reserved.
///
/// Licensed under the MIT License.
/// See LICENSE file in the project root for full license information.
///
/// 2b13c8312f53d4b9202b6c8c0f0e790d10044f9a00d8bab3edf3cd287457c979
/// 29c355784a3921aa290371da87bce9c1617b8584ca6ac6fb17fb37ba4a07d191
///

#ifndef _LEFT_H_
#define _LEFT_H_

#include "mvt.h"


class left:public mvt
{
	public:
		left():mvt() {};
		left(int p):mvt(p) {};
		left(const left & b):mvt(b) {};
		~left() {};
		void move(sprite & s) {mov(s);};
		void mov(sprite &);
};


#endif