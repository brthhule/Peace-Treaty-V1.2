#include "Database.h"

Database::Database() {
	//For debugging
	CV::debugFunction("Database, Database");

	//Default
	pNum = 0;
	maxCommanders = 0;
	currentParticipant = NULL;

}

void Database::updateTurnResources() {
	//For debugging
	CV::debugFunction("Database, updateTurnResources");

	Participants* tempParticipant = new Participants;
	tempParticipant->updateTurnResourcesParticipant();
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
	//For debugging
	CV::debugFunction("Database, initializeParticipant");

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

	createCapitals();
}

std::vector <Participants> *Database::getParticipantsList() {
	//For debugging
	CV::debugFunction("Database, getParticipantsList");

	return &participantsList;
}

void Database::setMaxCommanders(int num) {
	//For debugging
	CV::debugFunction("Database, setMaxCommanders");

	maxCommanders = num;
}
int Database::getMaxCommanders() {
	//For debugging
	CV::debugFunction("Database, getMaxCommanders");

	return maxCommanders;
}

void Database::setCurrentParticipant(Participants* p) {
	//For debugging
	CV::debugFunction("Database, setCurrentParticipant");

	currentParticipant = p;
}

Participants *Database::getCurrentParticipant() {
	//For debugging
	CV::debugFunction("Database, getCurrentParticipant");

	return currentParticipant;
}

bool Participants::isPlayer() {
	//For debugging
	CV::debugFunction("Database, isPlayer");

	return playerStatus;
}

void Participants::setPlayerStatus(bool status) {
	//For debugging
	CV::debugFunction("Database, setPlayerStatus");

	playerStatus = status;
}

Participants *Database::getParticipant(int index) {
	//For debugging
	CV::debugFunction("Database, getParticipant");

	return &participantsList[index];
}




void Database::createCapitals() {
	//For debugging
	CV::debugFunction("Database, createCapitals()");

	for (Participants participant : participantsList) {
		start:
			std::pair<int, int> systemCoords;
			systemCoords.first = rand() % CV::continentSize;
			systemCoords.second = rand() % CV::continentSize;

			Provinces* province = participantsList[0].getSystemProvince(systemCoords);

			if (province->getParticipantIndex() == -1)
			{
				province->changeParticipantIndex(participant.getParticipantIndex());
				province->changeUnitName(participant.getNewName());
				participant.addProvince(province);
				participant.setCapital(province);
			}
			else
			{
				goto start;
			}
	}
	
}

void Database::createMap() {
	//For debugging
	CV::debugFunction("Database, createMap");

	Participants* tempParticipant = new Participants;
	tempParticipant->createMapParticipant();
	delete tempParticipant;
}