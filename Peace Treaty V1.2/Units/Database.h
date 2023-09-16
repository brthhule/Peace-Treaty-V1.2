#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>

//Units
#include "Participants.h"
#include "Provinces.h"
#include "CommanderPRofile.h"
#include "../Misc/OtherFunctions.h"
#include "../Misc/LinkedList.h"//might need to move Database up, out of Units, so it can have a larger scope

#define print(x) std::cout << x;
#define println(x) std::cout << x << std::endl;
#define RED "\033[31m"
#define WHITE "\033[0m"
#define BLUE "\033[;34m"
//constexpr int size = 10; // modern C++ same thing as #define SIZE 10



//Clase for an object that contians everything in the system/game
//Purpose: from now on, create 
class Database {
public:
	//Constructor
	Database();

	void createMap();
	void initializeParticipants(int totalPlayers, int humanPlayers);
	std::vector<Participants*> getParticipantsList ();
	void updateTurnResources();

	void setContinentSize(int num);
	int getContinentSize();
	void setMaxCommanders(int num);
	int getMaxCommanders();


private:
	OtherFunctions OF;
	std::vector<Participants> participantsList;
	std::unordered_map <int, Provinces*> provincesHH;
	std::vector <std::vector <Provinces>> provincesMap;
	int currentParticipantIndex;
	int turn = 1;
	int continentSize;
	//Linked list of provinces
	LinkedList provincesLL;
	int maxCommanders;
};

#endif