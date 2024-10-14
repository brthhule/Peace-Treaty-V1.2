//Map.h
//Base Class
//Inherited by Participants

#ifndef MAP_H 
#define MAP_H 

#include <iostream>
#include <vector>
#include <memory>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include PROVINCES_HEADER		//Composition 
#include INF_HEADER
#include INPUT_HEADER
#include LOG_HEADER

/*TODO
* Potentially implement lamda in showMap();
* Optomize getProvince (specifically getProvince for type USER)
*/
class Map {
public:
	//----Constructors---------------------------------------------------------
	Map();
	~Map();

	//----Mutators-------------------------------------------------------------
	///Creates the map
	static void setMap();
	///Iterate through all the Provinces:: and update resource amounts
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
	*		@return Provinces:: shared pointer
	*/	
	static PROV::provSPTR getProvince(COORD::CoordsType type, INF::ipair coords);
	//Prompts the user to pick a pair of x and y coordinates within the bounds of the map, returns USER type coords
	static INF::ipair pickCoords();
	static bool checkInBounds(INF::ipair coords, COORD::CoordsType type);

	///2D vector of Provinces:: (original context)
	static PROV::prov2Vector mapVectors; 
	///unordered map of Provinces:: shared pointers
	static PROV::provMAP mapMap;

private:
	void assignSurroundingProvinces(); 
	void assignSurroundingProvincesAux(int rowIndex, int colIndex, Provinces* currentProvince);
};
#endif