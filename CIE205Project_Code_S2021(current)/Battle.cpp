#include "Battle.h"
#include "Enemies/Fighter.h"
#include "Enemies/Freezer.h"
#include "Enemies/Healer.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include<iostream>

using namespace std;


Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		phase1();
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		break;
	};

	delete pGUI;
	
}

GAME_STATUS Battle::InteractiveMode()
{
	int ActiveNumbers, 
		FrozenNumbers;
	pGUI->PrintMessage("Start the game");
	pGUI->waitForClick();
	CurrentTimeStep = 0;
	ImportEnemies();
	AddAllListsToDrawingList();
	//pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.isForsted());	
	GAME_STATUS gameStatus = IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		pGUI->waitForClick();
		CurrentTimeStep++;
		//gameStatus = runTimeStep();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		/*FrozenNumbers = FrostedFighter + FrostedFreezer + FrostedHealer;
		ActiveNumbers = Q_Active.getC() - FrozenNumbers;
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), Q_Killed.getC(),
			ActiveNumbers, FrozenNumbers, ActiveFighter, ActiveFreezer, ActiveHealer,
			FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledFreezers, KilledHealer);*/
	}
	pGUI->waitForClick();
	return gameStatus;
}
GAME_STATUS Battle::StepByStepMode()
{

	int ActiveNumbers,
		FrozenNumbers;
	CurrentTimeStep = 0;
	ImportEnemies();
	AddAllListsToDrawingList();
	//pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted());	
	GAME_STATUS gameStatus = IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		Sleep(250);
		CurrentTimeStep++;
		//gameStatus = runTimeStep();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		/*FrozenNumbers = FrostedFighter + FrostedFreezer + FrostedHealer;
		ActiveNumbers = Q_Active.getC() - FrozenNumbers;
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.IsFrosted(), Q_Killed.getC(),
			ActiveNumbers, FrozenNumbers, ActiveFighter, ActiveFreezer, ActiveHealer,
			FrostedFighter, FrostedHealer, FrostedFreezer, KilledFighter, KilledFreezers, KilledHealer);*/
	}

	pGUI->waitForClick();
	return gameStatus;
}
GAME_STATUS Battle::SilentMode()
{
	CurrentTimeStep = 0;

	ImportEnemies();
	GAME_STATUS gameStatus = IN_PROGRESS;
	while (gameStatus == IN_PROGRESS)
	{
		CurrentTimeStep++;
		//gameStatus = runTimeStep();
	}

	pGUI->waitForClick();
	return gameStatus;
}

bool Battle::ImportEnemies() 
{
	ifstream inFile;
	inFile.open("Enemy2.txt");

	if (inFile.fail())
	{
		return false;
	}
	else
	{
		char* pch;
		char* context = nullptr;
		const int size = 300;
		char line[size];
		
		//variables to store data in
		int ID, ArrvTime, Dist;
		double Health, Speed, Power, RldPeriod;
		ENMY_TYPE type;

		//getting castle info from first line
		inFile.getline(line, size);

		pch = strtok(line, " ");
		BCastle.SetHealth(atoi(pch));
						
		pch = strtok(nullptr, " ");
		BCastle.SetEnemyNumber(atoi(pch));
		pch = strtok(nullptr, " ");
		BCastle.SetPower(atoi(pch));
		
		//getting number of enemies
		inFile.getline(line, size);
		pch = strtok(line, " ");
		NumEnmy = atoi(pch);
			
		
		//getting enemies info
		while (inFile.getline(line, size)) 
		{
			Enemy* pE;
				pch = strtok(line, " ");
				ID = atoi(pch);
				pch = strtok(nullptr, " ");
				type = (ENMY_TYPE)atoi(pch);
				pch = strtok(nullptr, " ");
				ArrvTime = atoi(pch);
				pch = strtok(nullptr, " ");
				Health = atoi(pch);
				pch = strtok(nullptr, " ");
				Power = atoi(pch);
				pch = strtok(nullptr, " ");
				RldPeriod = atoi(pch);
				pch = strtok(nullptr, " ");
				Speed = atoi(pch);

				//initiating enemies according to their types then adding them to inactive queue
		switch (type)
		{
		case FIGHTER:
			pE = new Fighter(ID, ArrvTime, Speed, Power, RldPeriod);
			fighterNum++;
			EnemyCount++;
			break;
		case HEALER:
			pE = new Healer(ID, ArrvTime, Speed, Power, RldPeriod);
			healerNum++;
			EnemyCount++;
			break;
		case FREEZER:
			pE = new Freezer(ID, ArrvTime, Speed, Power, RldPeriod);
			freezerNum++;
			EnemyCount++;
		};
		Q_Inactive.enqueue(pE);
		}
		inFile.close();
	}
	return true;
}
void Battle::ExportData(GAME_STATUS gameStatus)
{
	ofstream fout("Play results.txt");
	Enemy* EnemyPointer;
	int TotalKills = Q_Killed.GetLength();
	int sumFirstShotDelay = 0;
	int sumKillDelay = 0;

	fout << "Game is:-  ";
	if (gameStatus == WIN)
	{
		fout << "WIN\n";
	}
	else if (gameStatus == LOSS)
	{
		fout << "LOSS\n";
	}
	else if (gameStatus == DRAWN)
	{
		fout << "DRAWN\n";
	}

	fout << "KTS  ID   FD   KD   LT\n";
	for (int i = 0; i < TotalKills; i++)
	{

		Q_Killed.dequeue(EnemyPointer);

		//outputting KTS
		if (EnemyPointer->GetKilledTime() < 10)
		{
			fout << EnemyPointer->GetKilledTime() << "    ";
		}
		else if (EnemyPointer->GetKilledTime() < 100)
		{
			fout << EnemyPointer->GetKilledTime() << "   ";
		}
		else if (EnemyPointer->GetKilledTime() < 1000)
		{
			fout << EnemyPointer->GetKilledTime() << "  ";
		}

		//outputting ID
		if (EnemyPointer->GetID() < 10)
		{
			fout << EnemyPointer->GetID() << "    ";
		}
		else if (EnemyPointer->GetID() < 100)
		{
			fout << EnemyPointer->GetID() << "   ";
		}
		else if (EnemyPointer->GetID() < 1000)
		{
			fout << EnemyPointer->GetID() << "  ";
		}

		//outputting FD
		sumFirstShotDelay += EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime();
		if (EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() < 10)
		{
			fout << EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() << "    ";
		}
		else if (EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() < 100)
		{
			fout << EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() << "   ";
		}
		else if (EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() < 1000)
		{
			fout << EnemyPointer->getfirstShotTime() - EnemyPointer->GetArrvTime() << "  ";
		}

		//outputting KD
		sumKillDelay += EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime();
		if (EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() < 10)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() << "    ";
		}
		else if (EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() < 100)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() << "   ";
		}
		else if (EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() < 1000)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->getfirstShotTime() << "  ";
		}

		//outputting LT
		if (EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() < 10)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() << "    ";
		}
		else if (EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() < 100)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() << "   ";
		}
		else if (EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() < 1000)
		{
			fout << EnemyPointer->GetKilledTime() - EnemyPointer->GetArrvTime() << "  ";
		}
		fout << endl;
	}

	fout << BCastle.getTotalDamage() << endl;

	if (gameStatus == WIN)
	{
		fout << "Total Enemies = " << TotalKills << endl;
		fout << "Average First-Shot Delay = " << 1.0 * sumFirstShotDelay / TotalKills << endl;
		fout << "Average Kill Delay = " << 1.0 * sumKillDelay / TotalKills << endl;
	}
	else
	{
		fout << "Killed Enemies = " << TotalKills << endl;
		fout << "Alive Enemies = " << EnemyCount - TotalKills << endl;
		fout << "Average First-Shot Delay for killed = " << 1.0 * sumFirstShotDelay / TotalKills << endl;
		fout << "Average Kill Delay for killed = " << 1.0 * sumKillDelay / TotalKills << endl;
	}
}

void Battle::phase1()
{
	CurrentTimeStep = 0;
	ImportEnemies();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		Update();	//Randomly update enemies distance/status (for demo purposes only)
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		pGUI->waitForClick();
	}
}

void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int c1, c2, c3, c4;
	Enemy* const* EnemyList = Q_Inactive.toArray(c1);
	Fighter* const* FighterList = Q_Fighter.toArray(c2);
	Freezer* const* FreezerList = Q_Freezer.toArray(c3);
	Healer* const* HealerList = S_Healer.toArray(c4);
	for (int i = 0; i < c1; i++)
		pGUI->AddToDrawingList(EnemyList[i]);
	for (int i = 0; i < c2; i++)
		pGUI->AddToDrawingList(FighterList[i]);
	for (int i = 0; i < c3; i++)
		pGUI->AddToDrawingList(FreezerList[i]);
	for (int i = 0; i < c4; i++)
		pGUI->AddToDrawingList(HealerList[i]);
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		
		switch (pE->GetType())
		{
		case HEALER:
			S_Healer.push(dynamic_cast<Healer*> (pE));
			break;
		case FIGHTER:
			Q_Fighter.insert(dynamic_cast<Fighter*> (pE), dynamic_cast<Fighter*> (pE)->getPriority());
			break;
		case FREEZER:
			Q_Freezer.enqueue(dynamic_cast<Freezer*> (pE));
			break;
		};
			
	}
}

void Battle
//Randomly update enemies distance/status (for demo purposes)
//void Battle::Update()	
//{
//	Enemy* pE;
//	Fighter* pFighter;
//	Freezer* pFreezer;
//	Healer* pHealer;
//	Queue< Enemy*> temp;
//	int freeze_counter=2, actvkil=1, frstkil=1;
//	Q_Fighter.dequeueMax(pFighter);
//	pE->SetStatus(FRST);
//	Q_Fighter.insert(pE);
//	Q_Fighter.dequeue(pE);
//	pE->SetStatus(FRST);
//	Q_Fighter.enqueue(pE);
//	Q_Freezer.dequeue(pE);
//	pE->SetStatus(FRST);
//	Q_Freezer.enqueue(pE);
//	Q_Freezer.dequeue(pE);
//	pE->SetStatus(FRST);
//	Q_Freezer.enqueue(pE);
//	Q_Healer.dequeue(pE);
//	pE->SetStatus(FRST);
//	Q_Healer.enqueue(pE);
//	Q_Healer.dequeue(pE);
//	pE->SetStatus(FRST);
//	Q_Healer.enqueue(pE);
//
//	while(Q_Fighter.dequeue(pE))
//	{
//		switch(pE->GetStatus())
//		{
//		case ACTV:
//			if (actvkil) {
//				pE->SetStatus(KILD);
//				actvkil = !actvkil;
//			}
//			pE->DecrementDist();
//			break;
//		case FRST:
//			if (frstkil) {
//				pE->SetStatus(KILD);
//				frstkil = !frstkil;
//			}
//			if (freeze_counter > 0) {
//				pE->SetStatus(ACTV);
//				freeze_counter--;
//			}
//			break;
//		}
//		temp.enqueue(pE);
//	}
//	while (temp.dequeue(pE))Q_Fighter.enqueue(pE);
//	while (Q_Freezer.dequeue(pE))
//	{
//		switch (pE->GetStatus())
//		{
//		case ACTV:
//			if (actvkil) {
//				pE->SetStatus(KILD);
//				actvkil = !actvkil;
//			}
//			pE->DecrementDist();
//			break;
//		case FRST:
//			if (frstkil) {
//				pE->SetStatus(KILD);
//				frstkil = !frstkil;
//			}
//			if (freeze_counter > 0) {
//				pE->SetStatus(ACTV);
//				freeze_counter--;
//			}
//			break;
//		}
//		temp.enqueue(pE);
//	}
//	while (temp.dequeue(pE))Q_Freezer.enqueue(pE);
//	while (Q_Healer.dequeue(pE))
//	{
//		switch (pE->GetStatus())
//		{
//		case ACTV:
//			if (actvkil) {
//				pE->SetStatus(KILD);
//				actvkil = !actvkil;
//			}
//			pE->DecrementDist();
//			break;
//		case FRST:
//			if (frstkil) {
//				pE->SetStatus(KILD);
//				frstkil = !frstkil;
//			}
//			if (freeze_counter > 0) {
//				pE->SetStatus(ACTV);
//				freeze_counter--;
//			}
//			break;
//		}
//		temp.enqueue(pE);
//	}
//	while (temp.dequeue(pE))Q_Healer.enqueue(pE);
//}
