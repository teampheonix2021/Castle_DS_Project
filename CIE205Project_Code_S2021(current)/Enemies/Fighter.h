#pragma once
#include "Enemy.h"
class Fighter:public Enemy
{
private:
	int priority;
public:
	Fighter(int ID, int AT, double S, double P, double RP, int d = MaxDistance);
	int getPriority() 
	{
		return (Power*status) - (Distance+Health+RldPeriod);
	}
};
