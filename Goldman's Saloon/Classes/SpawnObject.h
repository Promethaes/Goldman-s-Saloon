#pragma once
#include <random>
class SpawnObject
{
public:
	SpawnObject();
	SpawnObject(float timerMin = 0.0f, float timerVariance = 0.0f, unsigned int chain = 0)
		: spawnTimerMin(timerMin), spawnTimerVariance(timerVariance), amountVariance(chain) {}
	int update(float);
private:
	
	float spawnTimer = 0.0f;
	float spawnTimerMin = 0.0f;
	float spawnTimerVariance = 0.0f;
	float spawnTimerCurrentVariance = 0.0f;
	bool chainType = false;
	unsigned int amountVariance = 0;
};