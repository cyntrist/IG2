#include "Bat.h"

void Bat::updateAnim()
{
	if (timer->getMilliseconds() > ROT_TIMER)
	{
		timer->reset();
		sentido = -sentido;
	}

	brazoIzq->rotate(Quaternion(Radian(ROT_FACTOR * sentido), Vector3(0, 0, 1)));
	brazoDer->rotate(Quaternion(Radian(-ROT_FACTOR * sentido), Vector3(0, 0, 1)));
}
