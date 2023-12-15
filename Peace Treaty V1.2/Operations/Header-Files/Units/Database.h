#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace INF;

//constexpr int size = 10; // modern C++ same thing as #define SIZE 10

//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database
	COMPRISES_
		
	USES_ 
		INF_NAMESPACE
{
public:
	//Constructor
	Database();

	void createMap();
	void initializeParticipants(int totalPlayers, int humanPlayers);
	void updateTurnResources();
	void setMaxCommanders(int num);
	void setCurrentParticipant(partSPTR p);
	void createCapitals();

	
	std::vector<Participants>* getParticipantsList();
	
	partSPTR getCurrentParticipant();
	partSPTR getParticipant(int index);


private:
	
	std::vector<Participants> participantsList;
	partSPTR currentParticipant;
};

#endif