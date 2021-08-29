#include "Healer.h"


Healer::Healer(int id, double health, int arrTime, double speed, double power, double ReloadPeriod) :Enemy(id, health, HEALER, arrTime, speed, power, ReloadPeriod)
{

}
 
void Healer::Move() 
{
	
	if (CurrentHealth < 0.5 * Health)
	{
		if (Distance <= MinDistance)
		{
			Distance += 0.5 * GetSpeed();
		}
		else if (Distance >= MaxDistance)
		{
			Distance -= 0.5 * GetSpeed();
		}
	}
	else
	{
		if (Distance <= MinDistance)
		{
			Distance += GetSpeed();
		}
		else if (Distance >= MaxDistance)
		{
			Distance -=GetSpeed();
		}
	}
}

void Healer::HealEnemy(Enemy* enemy) 
{
	if (GetRldTime() != 0)
		return;

}