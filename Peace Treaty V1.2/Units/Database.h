#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

//Units
#include "Participants.h"
#include "Provinces.h"
#include "CommanderPRofile.h"
#include "../Misc/OF.h"
#include "../Misc/LinkedList.h"//might need to move Database up, out of Units, so it can have a larger scope
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
	
	int getMaxCommanders();

	Participants *getCurrentParticipant(),
				 *getParticipant(int index);


	class Mobility {
	public:
		static void moveUnitOne(CommanderProfile *commander);
		static std::vector <Provinces*> moveUnitTwo(CommanderProfile *commander);
	};

	static std::pair<int, int> pickCoords();

	Mobility move;

private:
	
	std::vector<Participants> participantsList;
	Participants* currentParticipant;

	

	int 
		maxCommanders,
		pNum; //have to fix this; current points to nothing
};

#endif