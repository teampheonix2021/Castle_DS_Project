#include "Healer.h"


Healer::Healer(int id, int AT, double S, double P, double RP, int d) : Enemy::Enemy(id, HEALER, AT, S, P, RP, d)
{
}