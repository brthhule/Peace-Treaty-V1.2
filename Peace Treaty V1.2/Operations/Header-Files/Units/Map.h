//Map.h
//Base Class
//Inherited by Participants

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PROVINCES_HEADER				//Composition
#include INF_HEADER						//Utility

using namespace INF;
using namespace PROV;
using namespace COORD;

/*TODO
* Potentially implement lamda in showMap();
* Optomize getProvince (specifically getProvince for type USER)
*/
class Map {
public:
	//----Constructors---------------------------------------------------------
	Map() {}
	~Map(){}

	//----Mutators-------------------------------------------------------------
	///Creates the map
	static void setMap();
	///Iterate through all the provinces and update resource amounts
	static void updateTurnResources();

	//----Printers-------------------------------------------------------------
	///Shows the map
	static void showMap();

	///Takes a coordinate, assigns the proper map symbol and color, prints
	static void meat(int x, int y);
	///Auxiliary method of showMap(), self explanatory
	static void printXAxis();
	
	//----Getters--------------------------------------------------------------
	/** getProvince__
	*		Takes in coords for province type CoordsType, returns province
	*		
	*		@param type__ SYSTEM or USER
	*		@param coords__ the pair of coords corresponding to SYSTEM/USER
	*		@return Provinces shared pointer
	*/	
	static provSPTR getProvince(CoordsType type, ipair coords);

	
	typedef std::unordered_map <std::string, provSPTR> ProvincesMap;
	typedef std::vector <std::vector<provSPTR>> ProvincesVector;

	///2D vector of provinces shared ptrs
	static ProvincesVector map;
	///unordered map of provinces shared pointers
	static ProvincesMap mapMap;
};
#endif