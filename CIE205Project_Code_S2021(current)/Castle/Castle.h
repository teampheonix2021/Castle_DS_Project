#pragma once
#include "..\Defs.h"
class Castle
{
	double Health,Power;
	int enmyNum;

	//
	// TODO: Add More Data Members As Needed
	//

public:
	bool isForsted = 0;
	Castle();
	Castle(double h, int n, double CP);
	void SetHealth(double h);
	void SetPower(double pwr);
	void SetEnemyNumber(int n);
	double GetHealth() const;
	

	//
	// TODO: Add More Member Functions As Needed
	//

};

