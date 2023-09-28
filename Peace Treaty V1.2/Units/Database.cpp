#include "Database.h"

Database::Database() {
	//provincesUM = provincesLL.createMap();
}

void Database::createMap() {
	OF.debugFunction("main, createMap--review");
	/*Basically create the map-- make each province an object of Provinces*/
	// int a = 1;
	// for (int x = 0; x < continentSize; x++) 
	// {
	 //    std::vector<Provinces> vectorThingy;
	 //    provincesMap.push_back(vectorThingy);
	 //    for (int y = 0; y < continentSize; y++) {
	// 	Provinces newProvince(x-1, y, -1);
	// 	newProvince.assignLinkedListNumber(a);
	// 	a++;
	// 	std::cout << ""
	// 	provincesLL.addNode(newProvince);
	// 	provincesHH[a] = &newProvince;
	// 	provincesMap[x].push_back(newProvince);
	 //    }
	 //  }
	try {
		//Need to change this to unordered map
		std::vector<Provinces>* allProvinces = provincesLL.createMap(continentSize);
		for (int x = 0; x < (int)allProvinces->size(); x++)
		{
			//Evaluate if this is what I want to do
			std::pair<int, Provinces*> thang = { x, &allProvinces->at(x) };
			//Fix this later
			//provincesHH[x] = thang;
		}

		provincesLL.listProvinces();
	}
	catch (...) {
		std::cout << "Error occurred...";
	}
			
	
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
	for (int x = 0; x < pNum; x++)
	{
		std::cout << "Creating participant " << x + 1 << ": " << std::endl;
		Participants newParticipant(x);

		//Create players many players
		if (x < totalPlayers /*I don't know if this is right*/) {
			newParticipant.createAsPlayer(true);
		} /*Everyone else is enemy AI*/ else {
			newParticipant.createAsPlayer(false);
		}

		participantsList.push_back(newParticipant);
	}

}

std::vector <Participants> *Database::getParticipantsList() {
	return &participantsList;
}

void Database::updateTurnResources() {
	OF.debugFunction("main, updateTurnResources");
	for (int x = 0; x < continentSize; x++) {
		for (int y = 0; y < continentSize; y++) {
			provincesMap[x][y].updateBuildingsProduction();
			provincesMap[x][y].updateProvinceResources();
		}
	}

	//LL Alternative:
	provincesLL.LLupdateprovinceResources();
}

void Database::setContinentSize(int num) {
	continentSize = num;
}
int Database::getContinentSize() {
	return continentSize;
}
void Database::setMaxCommanders(int num) {
	maxCommanders = num;
}
int Database::getMaxCommanders() {
	return maxCommanders;
}

void Database::showMap() {
	int LLNumber = 1;
	std::cout << "Map: \n";

	int thingy = continentSize;
	for (int x = 0; x < continentSize; x++) {
		// Y axis stuff
		if (thingy < 10)
			std::cout << " " << thingy << "| ";
		else
			std::cout << thingy << "| ";

		thingy--;
		// End y axis stuff

		for (int y = 0; y < continentSize; y++) {
			char letter = ' '; // Fix this later
			Provinces* showMapProvince = provincesHH[LLNumber];
			LLNumber++;

			if (showMapProvince->getParticipantIndex() == currentParticipantIndex)
			{
				std::cout << BLUE;
				if (showMapProvince->isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else if (showMapProvince->getParticipantIndex() != -1)
			{
				std::cout << RED;
				if (provincesMap[x][y].isCapital() == true)
					letter = 'C';
				else
					letter = 'p';
			}
			else {
				letter = '0';
			}

			std::cout << letter << showMapProvince->commandersNum();
			//std::cout << "  ";
			std::cout << LLNumber - 1 << " ";
			std::cout << WHITE;
		}
		std::cout << std::endl;
	}

	// X axis stuff
	std::cout << "    ";
	for (int a = 0; a < continentSize - 1; a++) {
		std::cout << "----";
	}
	std::cout << "--";
	std::cout << std::endl;
	std::cout << "    ";
	for (int a = 0; a < continentSize; a++) {
		if (a < 9)
			std::cout << a + 1 << "   ";
		else
			std::cout << a + 1 << "  ";
	}
	std::cout << "\n\n";
}
