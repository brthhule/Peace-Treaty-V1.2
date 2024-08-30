#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"

#include BUILDINGS_BASE_HEADER  
#include RESOURCE_BUILDINGS_HEADER  
#include BARRACKS_HEADER
#include INFIRMARY_HEADER
#include LIBRARY_HEADER
#include RESIDENCES_HEADER
#include WALL_HEADER
#include BUILD_HEADER
#include INF_HEADER

class Buildings {
public:
	Buildings();
	INF::i5array getResourceProduction(BUILD::BuildingsEnum name, INF::Quantity amount);
	
	//Returns an array of Resource/Other buildings levels

	INF::i5array getTypeLevels(BUILD::BuildingType type);
	BuildingsBASE& getBuilding(BUILD::BuildingsEnum name);
	BuildingsBASE& getBuilding(int num);
	int getResourceBuildingProduction(int buildingIndex);


	BuildingsBASE* at(int index) {
		return allBuildings.at(index); 
	}

	ResourceBuildings* getResourceBuilding(BUILD::BuildingsEnum type);

	Buildings* getBuildings();

	void mutateLevel(BUILD::BuildingsEnum name, INF::MutateDirection direction, int amount);
	void addTroopsTrainedThisTurn(int amount);
	void resetTroopsTrainedThisTurn();
	void initiailizeCapitalBuildings();

	//----Printers---------------------------------------------------------
	void printBuildingStats();

	///////////////////////////////////Getters/////////////////////////////////
	//Returns an array of Resource/Other buildings levels


	int getCapacity(BUILD::BuildingsEnum name);
	int getTroopsTrainedThisTurn();
	int getProvinceLevel();

	void printListOfBuildings();


private:

	std::array <BuildingsBASE*, 10> allBuildings; 
	Barracks barracks; 
	Infirmary infirmary; 
	Library library; 
	Residences residences; 
	Wall wall; 

	std::array<ResourceBuildings, 5> resourceBuildings;

};

#endif


/*
	struct Iterator {
		//Tags
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = BuildingsBASE;
		using pointer = BuildingsBASE*;  // or also value_type*
		using reference = BuildingsBASE&;  // or also value_type&

		//Constructor
		Iterator(pointer ptr) : m_ptr(ptr) {}

		//Operations
		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() { m_ptr++; return *this; }

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};

	Iterator begin() { return Iterator(&m_data[0]); }
	Iterator end() { return Iterator(&m_data[10]); } // 10 is out of bounds



	*/