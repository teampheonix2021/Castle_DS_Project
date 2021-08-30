#include "Castle.h"


Castle::Castle() 
{

}
Castle::Castle(double h, int n, double CP):enmyNum(n),Power(CP) 
{
	SetHealth(h);
};
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
bool Castle::IsFrosted() const
{
	return frosted;
}