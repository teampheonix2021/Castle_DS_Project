#pragma once
#include "Enemy.h"
class Healer:public Enemy
{
public:
	Healer(int ID, int AT, double S, double P, double RP, int d = MaxDistance);
};

