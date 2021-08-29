#include "Enemy.h"
#include<iostream>
using namespace std;
Enemy::Enemy()
{
	SetDistance(MaxDistance);
	SetStatus(INAC);
}

Enemy::Enemy(int id, ENMY_TYPE t, int arrTime, double s, double p, double RP, int d):ID(id),ArrvTime(arrTime),Type(t),Speed(s),Power(p),RldPeriod(RP)
{
	SetDistance(d);
	SetStatus(INAC);
}


Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance - Speed > MinDistance)
		Distance -= Speed;
	else if (Distance > MinDistance) {
		if (Type == HEALER)Speed = -Speed;
		Distance = MinDistance;
	}
	if (Distance > MaxDistance) {
		Distance = MaxDistance;
		Speed = -Speed;
	}
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}
ENMY_TYPE Enemy::GetType() const
{
	return Type;
}