#include "Castle.h"


Castle::Castle() 
{
}

Castle::Castle(double h, int n, double CP):enmyNum(n),Power(CP) 
{
	SetHealth(h);
	maximumhealth = h;
}

void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

void Castle::SetPower(double pwr)
{
	Power = pwr;
}

void Castle::SetEnemyNumber(int n)
{
	enmyNum = n;
}

double Castle::GetHealth() const
{
	return Health;
}


void Castle::attack(Enemy* enemy)
{
	if (frosted == true)
	{
		return;
	}
	else
	{
		srand(time(NULL));
		int icefire = rand() % 100;
		if (icefire <= 20)
		{
			if (enemy->GetStatus() != FRST)
			{
				if (enemy->gettotalice() >= 5)
				{
					enemy->SetStatus(FRST);
				}
				else
				{
					enemy->settotalice(1);
				}
			}
		}
		else
		{
			Healer* healer = dynamic_cast<Healer*>(enemy);
			int K = 0;
			if (Frozen == true)
			{
				return;
			}

			if (healer != nullptr)
			{
				K = 2;
			}
			else
			{
				K = 1;
			}
			double dmg = Power / (enemy->GetDistance() * K);
			castletotaldmg += dmg;
			enemy->BeDamaged(dmg);
		}
	}
}


void Castle::usehealertools(Enemy* enemy)
{
	Healer* healer = dynamic_cast<Healer*>(enemy);
	if (healer == nullptr)
	{
		return;
	}
	else
	{
		if (healer->IsDead() == true && healer->GetDistance() <= 5)
		{
			Health = 0.03 * maximumhealth;
		}
	}
}


bool Castle::isfrosted()
{
	return frosted;
}

bool Castle::getkilled()
{
	return iskilled;
}


void Castle::Bedamaged(double dmg)
{
	totaldmgtaken += dmg;
	Health -= dmg;
	if (Health <= 0)
	{
		Health = 0;
		iskilled = true;
	}
}


void Castle::Befrosted(double dmg)
{
	totalfrosttaken += dmg;
	if (totalfrosttaken >= castlethreshhold)
	{
		totalfrosttaken = 0;
		frosted = true;;
	}
}
