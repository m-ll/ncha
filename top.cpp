#include "top.h"

void top::mov(sprite & s)
{
	s.get_ys()-=get_pas();
	if(s.get_ys()+s.get_ht()<0)
	{
		s.get_a()=0;
		s.get_aff()=0;
	}
}