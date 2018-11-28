#include "left.h"

void left::mov(sprite & s)
{
	s.get_xs()-=get_pas();
	if(s.get_xs()+s.get_wt()<0)
	{
		s.get_a()=0;
		s.get_aff()=0;
	}
}