#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	 int ID;         //Each enemy has a unique ID (sequence number)
	 int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	ENMY_TYPE Type;
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	
	//
	// TODO: Add More Data Members As Needed
	//
	 double Speed;
	 double Power;
	 double RldPeriod;
	 int killedTime;		//Time at which an Enemy was killed
	 int firstShotTime = 0;	//Time at which an Enemy was first shot by the castle
public:
	Enemy();
	Enemy(int id,ENMY_TYPE t, int arrTime,double Speed,double Power, double RldPeriod, int d = MaxDistance);
	virtual ~Enemy();

	int GetID() const;
	ENMY_STATUS GetStatus() const;
	ENMY_TYPE GetType() const;
	
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );
	int GetDistance() const;

	int GetArrvTime() const;
	int GetKilledTime();

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	//All enemies can move
	//virtual void Act() = 0;	//Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	//

};

