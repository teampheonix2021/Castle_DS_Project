#pragma once

#include "Enemies/Enemy.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS/PriorityQueue.h"
#include "Generic_DS/ArrayStack.h"
#include "GUI\GUI.h"

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int CurrentTimeStep;
	int NumEnmy;
	int fighterNum = 0;
	int freezerNum = 0;
	int healerNum=0;


	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		            //Queue for inactive enemies
	Queue<Enemy*> Q_Killed;						//Queue for killed Enemies
	Queue<Enemy*> Q_Active;	                    //Queue for active Enemies
	Queue<Enemy*> Frozen;                       //Queue for frozen enemies
	PriorityQueue<Fighter*> Q_Fighter;          //queue for fighters enemies
	Queue<Freezer*> Q_Freezer;                  //queue for Freezer enemies
	ArrayStack<Healer*> S_Healer;               //stack for Healer enemies
	

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	bool ImportEnemies();		//Import enemies from a text file
	void ExportData(GAME_STATUS gameStatus);
	void phase1();
	void Update();
	GAME_STATUS CastleAttack();
	GAME_STATUS InteractiveMode();
	GAME_STATUS StepByStepMode();
	GAME_STATUS SilentMode();
};

