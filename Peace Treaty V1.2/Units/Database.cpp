#include "Database.h"

Database::Database() {
	provincesList = provincesLL.createMap();
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
	std::vector<Provinces*> allProvinces = provincesLL.createMap(continentSize);
	for (int x = 0; x < (int)allProvinces.size(); x++)
		provincesHH[x] = allProvinces[x];

	provincesLL.listProvinces();
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
	for (int x = 0; x < pNum; x++)
	{
		std::cout << "Creating participant " << x + 1 << ": " << std::endl;
		Participants newParticipant(x);

		//Create players many players
		if (x < players) {
			newParticipant.createAsPlayer(true);
		} /*Everyone else is enemy AI*/ else {
			newParticipant.createAsPlayer(false);
			
		}

		participantsList.push_back(newParticipant);
	}

}

vector <Participants*> Database::getParticipantsList() {
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
	return maxCommanders;
}
int Database::getMaxCommanders() {
	return maxCommanders;
}