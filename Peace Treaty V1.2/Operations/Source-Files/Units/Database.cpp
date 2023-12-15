#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include DATABASE_HEADER



Database::Database() {
	//For debugging
	INF::debugFunction("Database, Database");

	//Default
	maxCommanders = 0;
	currentParticipant = NULL;

}

void Database::updateTurnResources() {
	//For debugging
	INF::debugFunction("Database, updateTurnResources");

	partSPTR tempParticipant = new Participants;
	tempParticipant->updateTurnResourcesParticipant();
}

void Database::initializeParticipants(int totalPlayers, int humanPlayers) {
	//For debugging
	INF::debugFunction("Database, initializeParticipant");

	for (int x = 0; x < totalPlayers; x++)
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
	INF::debugFunction("Database, getParticipantsList");

	return &participantsList;
}

void Database::setCurrentParticipant(partSPTR p) {
	//For debugging
	INF::debugFunction("Database, setCurrentParticipant");

	currentParticipant = p;
}

Participants *Database::getCurrentParticipant() {
	//For debugging
	INF::debugFunction("Database, getCurrentParticipant");

	return currentParticipant;
}

bool Participants::isPlayer() {
	//For debugging
	INF::debugFunction("Database, isPlayer");

	if (participantIndex < 0) {
		return false;
	}

	return true;
}

Participants *Database::getParticipant(int index) {
	//For debugging
	INF::debugFunction("Database, getParticipant");

	return &participantsList[index];
}




void Database::createCapitals() {
	//For debugging
	INF::debugFunction("Database, createCapitals()");

	for (Participants participant : participantsList) {
		start:
			ipair systemCoords;
			systemCoords.first = rand() % INF::continentSize;
			systemCoords.second = rand() % INF::continentSize;

			provSPTR province = participantsList[0].getSystemProvince(systemCoords);

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
	INF::debugFunction("Database, createMap");

	partSPTR tempParticipant = new Participants;
	tempParticipant->createMapParticipant();
	delete tempParticipant;
}