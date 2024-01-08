#ifndef TROOP_H
#define TROOP_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER

namespace TROOP {
	/*REGULAR, INJURED, LOST */
	enum TroopCondition {
		REGULAR,
		INJURED,
		LOST
	};

	/*DEFENSE, FIELD, ATTACK*/
	enum CombatTypes {
		DEFENSE = 0,
		FIELD = 1,
		ATTACK = 2
	};

	/*	GUARDS, INFANTRY, ARCHERS, CAVALRY, ARTILLARY*/
	enum TroopTypes {
		GUARDS,
		INFANTRY,
		ARCHERS,
		CAVALRY,
		ARTILLARY
	};

	
	extern INF::s5array TROOP_NAMES;
	//Check out spelling below??
	extern INF::i5array TROOPS_COST, TROOPS_CP;
	extern int maxCommanders;

	TroopTypes stringToTroopType(std::string type);
}

#endif
