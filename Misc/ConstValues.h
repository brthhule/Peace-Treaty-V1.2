#ifndef CONSTVALUES_H
#define CONSTVALUES_H

#include <iostream>
#include <array>

#define UNIT_AMOUNT 5

class ConstValues 
{
public:
	ConstValues();

  const std::array<std::string, UNIT_AMOUNT> TROOP_NAMES = { "Militia", "Guards", "Cavalry", "Knights", "Paladins" };
  const std::array<std::string, UNIT_AMOUNT> RESOURCE_BUILDING_NAMES = { "Farm", "Lumber Mill", "Quarry", "Mine", "Church" };
  const std::array<std::string, 5> OTHER_BUILDING_NAMES = {"Barracks","Infirmary","Library","Wall","Residences"};
  const std::array<std::string, UNIT_AMOUNT> RESOURCE_NAMES = { "Food", "Wood", "Ore", "Gold", "Mana" };
  
  const std::array<int, UNIT_AMOUNT> TROOPS_COST = { 5, 4, 3, 2, 1 };
  const std::array<int, UNIT_AMOUNT> INITIAL_VALUES = { 5, 4, 3, 2, 1 };
  const std::array<int, UNIT_AMOUNT> TROOPS_CP = { 1,2,4,8,16 };
  const std::array<int, UNIT_AMOUNT> RESOURCE_PRODUCTION = { 5,4,3,2,1};
  const int BARRACKS_PRODUCTION = 2;
};

#endif