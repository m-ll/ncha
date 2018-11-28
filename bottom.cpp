#include "bottom.h"

void bottom::mov(sprite & s)
{
	s.get_ys()+=get_pas();
	if(s.get_ys()>480)
	{
		s.get_a()=0;
		s.get_aff()=0;
	}
}