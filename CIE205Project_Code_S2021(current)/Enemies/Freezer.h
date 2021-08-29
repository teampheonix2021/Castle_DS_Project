#pragma once
#include "Enemy.h"
class Freezer:public Enemy
{
public:
	Freezer(int ID, int AT, double S, double P, double RP, int d = MaxDistance);
};

