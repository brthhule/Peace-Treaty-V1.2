#ifndef TROOP_H
#define TROOP_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include INF_HEADER

using namespace INF;

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

	
	extern i5array TROOP_NAMES;
	//Check out spelling below??
	extern i5array TROOPS_COST, Troops_CP;
	extern int maxCommanders;
}

#endif
