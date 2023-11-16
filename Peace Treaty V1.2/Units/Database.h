#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

//Units
#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"

#include "../Units/Misc/INF.h"


#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

//constexpr int size = 10; // modern C++ same thing as #define SIZE 10



//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database
{
public:
	//Constructor
	Database();

	void createMap(),
		initializeParticipants(int totalPlayers, int humanPlayers),
		updateTurnResources(),
		setMaxCommanders(int num),
		setCurrentParticipant(Participants* p),
		createCapitals();

	
	std::vector<Participants>* getParticipantsList();
	
	Participants* getCurrentParticipant();
	Participants* getParticipant(int index);


private:
	
	std::vector<Participants> participantsList;
	Participants* currentParticipant;
};

#endif