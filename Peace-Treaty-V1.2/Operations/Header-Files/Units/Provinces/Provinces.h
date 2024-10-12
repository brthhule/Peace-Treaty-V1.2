//Provinces::.h
//Inherits: PrimeUnits, BuildMA, Buildings

#ifndef PROVINCES_H
#define PROVINCES_H

#include <iostream>
#include <unordered_map>
#include <random>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include INPUT_HEADER					//Utility
#include INF_HEADER

#include BUILD_MA_HEADER				//Interface

#include PRIME_UNITS_HEADER					//Base Class
#include COORDS_BASE_HEADER				//Base Class
#include TROOP_UNITS_BASE_HEADER		//Composition
#include TROOP_HEADER
#include TROOPS_INT_HEADER				//Interface


#include COMMANDERS_HEADER				//Composition

#include PROVINCE_REPORT_HEADER			//Composition

#include BARRACKS_HEADER 
#include INFIRMARY_HEADER
#include LIBRARY_HEADER 
#include RESIDENCES_HEADER  
#include WALL_HEADER

#include BUILDINGS_HEADER

/*
Implement getLists, calculateCombatPower, calculateFoodConsumption
*/
class Provinces :
	public PrimeUnits,				//Base Class
	public BuildMA					//Interface
{
public:

	static enum RelativeDirection {
		LEFT_UP,
		UP,
		RIGHT_UP,
		LEFT, RIGHT,
		LEFT_DOWN,
		DOWN,
		RIGHT_DOWN
	};

	///////////////////////////////This Class//////////////////////////////
	//----Constructors-----------------------------------------------------
	Provinces(int mapIndex, int participantIndex);

	//Copy constructor
	Provinces(const Provinces &copyProvince);
	~Provinces() {}

	//----Initialization---------------------------------------------------
	bool isCapital() const;
	bool hasCommander(std::string name);
	/*Subtracts the necessary resources from capital province. If resources left over are all positive (there were enough resources), return true. If any resources are negative, return false*/
	bool subtractCheckResources(INF::constArrayRef resourcesArray);

	///Initializes this province as a capital
	void makeCapital(int participantIndexArg);
	/*///Sets this Provinces::' stats to capital when generating game.
	Sets all buildings to level 1*/
	void initializeCapitalStats();

	///Set the name of this kingdom
	void setKingdomName(std::string name);
	///Set map index of this province

	//----Getters----------------------------------------------------------
	///Return reference of commander by name
	Commanders& getCommander(std::string name);
	Commanders& getCommander(int index);
	Commanders getConstCommander(int index) const;
	//Returns vector of commanders in this province
	COMM::commSPTRList getAllCommanders() const;

	///Returns the total amount of Commanders this unit has
	int getCommandersNum() const;
	///Calculates the combat power of this province
	int getTotalCP() const;
	///Get the index of this unit in its Participant's vector?
	INF::constINT getMapIndex() const;

	Commanders & getProvinceCommander() const;
	INF::constINT getLevel() const override;

	//----Setters----------------------------------------------------------
	void addCommander(Commanders newCommander);
	void removeCommander(COMM::commSPTR newCommander);
	//Adds the resource production amounts to the resource totals*/
	void updateProvinceResources();

	///Create scout report for this province
	void createReport(int scouterLevelArg, int targetLevelArg);

	void printCommanders();

	int getTroopsTrainedThisTurn();


	///////////////////////////////////BuildMA/////////////////////////////////
	//----Printers-------------------------------------------------------------
	void printBuildingUpgradeCosts(INF::i5array requiredresources, int buildingindex) override;
	void upgradeBuildingPrompt() override,
		selectBuildingToUpgrade() override,
		upgradeBuilding(int buildingNumber) override;

	void setCommandersSortStatus(INF::SortType status);
	INF::SortType getCommandersSortStatus() const;

	std::string getKingdomName();

	std::array<INF::i5array, 7> getLists();
	std::array<int, 7> getListInt();
	std::array<bool, 2> getListBool();
	std::array< INF::ipair, 2> getListCoords();

	//Scout/report stuff
	std::array<INF::i5array, 4> getGeneralLists();

	int getCommanderIndex(COMM::commSPTR commander);

	//Implement these, add them to PrimeUnits later on
	void calculateCombatPower();
	void calculateFoodConsumption();
	///////////////////////////////PrimeUnits.h////////////////////////////////
	INF::constINT getCombatPower() const override;
	INF::constINT getFoodConsumption() const override;
	///////////////////////////////BuildingAttributesINT///////////////////////
		
	//----Getters--------------------------------------------------------------
	

	



	std::shared_ptr<Provinces> getRelativeProvince(RelativeDirection direction); 
	std::array<Provinces*, 8>* getRelativeDirectionList();
	void setRelativeProvince(RelativeDirection direction, Provinces* province);

	Buildings* getBuildings();

protected:
	enum Lists { 
		RESOURCE_BUILDINGS_LEVELS, 
		OTHER_BUILDINGS_LEVELS, 
		RESOURCES_PRESENT, 
		TROOPS_PRESENT, 
		TROOPS_INJURED, 
		TROOPS_LOST, 
		INITIAL_STATS 
	};

	enum ListsInt { 
		CP, 
		TOTAL_TROOPS, 
		FOOD_CONSUMPTION, 
		PARTICIPANT_INDEX, 
		UNIT_LEVEL, 
		TROOPS_TRAINED_THIS_TURN, 
		OVRALL_INDEX 
	};

	enum ListBool{ CAN_SELECT_THIS_UNIT, IS_CAPITAL, DELETE_PROVINCE };
	enum ListCoords { SYSTEM_COORDS, USER_COORDS };
	enum Report { REPORT_TURN, REPORT_LOG };

	

private:
	INF::SortType commandersSortType;
	bool isACapital;

	int mapIndex;

	int civilians;

	COMM::commMAP::iterator it;
	COMM::commMAP commandersMap;
	std::vector<Commanders> commandersVector; //Commanders live here
	///The main commander at this province
	COMM::commSPTR provinceCommander;

	double newAccuracy;
	std::string kingdomName;

	//Index within reports is the report. 
	// Index of report object is the participant the report belongs to
	typedef std::vector<std::pair<int, ProvinceReport >> Reports;
	std::vector<Reports> scoutReports;

	std::array<Provinces*, 8> nearbyProvinces;

	Buildings buildings;
	
};

namespace PROV {
	using provSPTR = std::shared_ptr<Provinces>;
	using provMAP = std::unordered_map<std::string, provSPTR>;
	using provSPTRList = std::vector<provSPTR>;
	using scoutTypes = std::pair<COMM::commSPTRList, PROV::provSPTRList>;
	using prov2Vector = std::vector <std::vector<Provinces>>;

	provSPTR make_provSPTR(Provinces& province_ref);
}
#endif
