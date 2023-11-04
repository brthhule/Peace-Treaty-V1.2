#include "../Peace Treaty V1.2/Misc/CV.h"

namespace CV {
	/*TROOP_NAMES = Militia, Guards, Cavalry, Knights, Paladins*/
	StringArray TROOP_NAMES = {
		"Militia",
		"Guards",
		"Cavalry",
		"Knights",
		"Paladins"
	};

	/*RESOURCE_BUILDING = Farm, Lumber Mill, Quarry, Mine, Church*/
	StringArray RESOURCE_BUILDING_NAMES = {
		"Farm",
		"Lumber Mill",
		"Quarry",
		"Mine",
		"Church"
	};

	/*OTHER_BUILDING = Barracks, Infirmary, Library, Wall, Residences*/
	StringArray OTHER_BUILDING_NAMES = {
				"Barracks",
				"Infirmary",
				"Library",
				"Wall",
				"Residences"
	};

	/*RESOURCE = Food, Wood, Ore, Gold, Mana*/
	StringArray RESOURCE_NAMES = {
				"Food",
				"Wood",
				"Ore",
				"Gold",
				"Mana"
	};

	/*TROOPS_COST = 5, 4, 3, 2, 1 */
	ConstNumerics TROOPS_COST = { 5, 4, 3, 2, 1 };

	/*INITIAL_VALUES = 5, 4, 3, 2, 1 */
	ConstNumerics INITIAL_VALUES = { 5, 4, 3, 2, 1 };

	/*TROOPS_CP = 1, 2, 4, 8, 16*/
	ConstNumerics TROOPS_CP = { 1,2,4,8,16 };

	/*RESOURCE_PRODUCTION = 5, 4, 3, 2, 1 */
	ConstNumerics RESOURCE_PRODUCTION = { 5,4,3,2,1 };


	/*"	SELECT_ENEMY_ACTION",
			"PLAYER_UNIT_ACTION",
			"INTRODUCTION",
			"PLAYER_ACTION",
			"ARMY_DEPLOYMENT",
			"TRAIN_MA_FUNCTION",
			"PLAYER_BUILD_FUNCTION",
			"VIEW_PLAYER_MAP",
			"SELECT_PLAYER_PROVINCE",
			"SELECT_ENEMY_PROVINCE",
			"WHAT_REPORT"*/
	std::array<std::string, 11> PROMPTS_STRING = {
			"SELECT_ENEMY_ACTION",
			"PLAYER_UNIT_ACTION",
			"INTRODUCTION",
			"PLAYER_ACTION",
			"ARMY_DEPLOYMENT",
			"TRAIN_MA_FUNCTION",
			"PLAYER_BUILD_FUNCTION",
			"VIEW_PLAYER_MAP",
			"SELECT_PLAYER_PROVINCE",
			"SELECT_ENEMY_PROVINCE",
			"WHAT_REPORT" /*Add stuff for this*/
	};

	std::array<std::string, 9> COLORS_STRING = {
			"BLACK",
			"RED",
			"GREEN",
			"YELLOW",
			"BLUE",
			"MAGENTA",
			"CYAN",
			"WHITE",
			"RESET"
	};

	int continentSize = 0;
	int enemyDifficulty = 0;
	int CPUNum = 0;
	int turn = 0;
	int UNIT_AMOUNT_CV = UNIT_AMOUNT;
	int currentParticipantIndex = 0;

	const int BARRACKS_PRODUCTION = 2;
}
