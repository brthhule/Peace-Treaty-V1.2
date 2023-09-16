#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "OtherFunctions.h"
#include "../Units/Provinces.h"

struct node
{
	//Data type
	Provinces* province;

	//Pointer to next node
	node *next;
};

class LinkedList
{
public:
	//Constructor
	LinkedList();

	//Add a node to the linked list; should not be called unless in createMap
	void addNode (Provinces &provinceArg);

	//Iterate through provinces, update their resources
	void LLupdateprovinceResources ();

	//Get how many provinces are in the linked list
	int getProvincesNum ();

	//Iterate through the linked list to return a province at an index
	Provinces* getProvinceByNum (int num);

	//Create the map of provinces; for 0 < size*size, create province objects and add to linked list. Returns the linked list as an unordered_map of pointers
	std::unordered_map<std::string, Provinces*> createMap(int size);

	//Show all provinces in linked list-- name and number in linked list
	void listProvinces();


private:
	//Head node
	node *head;

	//Tail node
	node *tail;

	//Amount of provinces in linkedlist
	int provincesNum;

	//Infrastructure stuff
	OtherFunctions OF;
	std::vector<Provinces*> allProvinces;
};


#endif