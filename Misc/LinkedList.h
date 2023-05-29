#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "OtherFunctions.h"
#include "../Units/Provinces.h"

struct node
{
	Provinces* province;
	node *next;
};

class LinkedList
{
public:
	LinkedList();

	void addNode (Provinces &provinceArg);
	void LLupdateprovinceResources ();
	int getProvincesNum ();
	Provinces* getProvinceByNum (int num);
	std::vector<Provinces*> createMap(int size);
	void listProvinces();


private:
	node *head;
	node *tail;
	int provincesNum;
	OtherFunctions OF;
};


#endif