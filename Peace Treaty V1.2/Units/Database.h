#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

//Units
#include "Participants.h"
#include "Provinces.h"
#include "CommanderPRofile.h"
#include "../Misc/OF.h"
#include "../Misc/LinkedList.h"//might need to move Database up, out of Units, so it can have a larger scope
#include "Map.h"
#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;

//constexpr int size = 10; // modern C++ same thing as #define SIZE 10



//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database : public Map
{
public:
	//Constructor
	Database();

	void createMap();
	void initializeParticipants(int totalPlayers, int humanPlayers);
	std::vector<Participants> *getParticipantsList ();
	void updateTurnResources();

	void setContinentSize(int num);
	int getContinentSize();
	void setMaxCommanders(int num);
	int getMaxCommanders();

	int *getContinentSizePointer() { return &continentSize; }
	void setCurrentParticipant(Participants *p) {
		currentParticipant = p;
	}
	Participants *getCurrentParticipant() {
		return currentParticipant;
	}

private:
	
	std::vector<Participants> participantsList;
	std::unordered_map <int, Provinces*> provincesUM;
	std::vector <std::vector <Provinces>> provincesMap;
	std::vector<Provinces> provincesList;
	Participants* currentParticipant;
	int currentParticipantIndex;
	
	int continentSize;
	//Linked list of provinces
	LinkedList provincesLL;
	int maxCommanders;

	int pNum; //have to fix this; current points to nothing
};

#endif