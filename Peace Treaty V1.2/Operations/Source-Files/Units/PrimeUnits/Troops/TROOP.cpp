#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include TROOP_HEADER

using namespace INF;

/*Troops_COST = 5, 4, 3, 2, 1 */
i5array TROOP::TROOPS_COST = { 5, 4, 3, 2, 1 };
/*Troops_CP = 1, 2, 4, 8, 16*/
i5array TROOP::TROOPS_CP = { 1,2,4,8,16 };

int TROOP::maxCommanders = 0;

/*TROOP_NAMES = Militia, Guards, Cavalry, Knights, Paladins*/
s5array TROOP::TROOP_NAMES = {
	"Militia",
	"Guards",
	"Cavalry",
	"Knights",
	"Paladins"
};

TROOP::TroopTypes TROOP::stringToTroopType(std::string type) {
	for (int x = 0; x < 5; x++) {
		if (TROOP_NAMES.at(x) == type) {
			return TroopTypes(x);
		}
	}

	//Error case
	return GUARDS;
}

