#include "SpawnObject.h"

SpawnObject::SpawnObject()
{
	//gottem
}

int SpawnObject::update(float dt)
{
	if (spawnTimer >=spawnTimerMin+spawnTimerCurrentVariance)
	{
		spawnTimer = 0.0f;
	}
	if (!spawnTimer)
	{
		spawnTimer += dt;
		spawnTimerCurrentVariance = (rand() % (int)spawnTimerVariance);
		if (amountVariance != 0)
			return 1 + (rand()%amountVariance);
		else
			return 1;
	}		
}

