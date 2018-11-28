#include "right.h"

void right::mov(sprite & s)
{
	s.get_xs()+=get_pas();
	if(s.get_xs()>640)
	{
		s.get_a()=0;
		s.get_aff()=0;
	}
}