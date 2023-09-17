#ifndef BUILD_H
#define BUILD_H

class Build
{
public:
	Build() {};
	virtual ~Build() {};
	virtual void playerBuildFunction() = 0;
	virtual void upgradeBuildings() = 0;
	virtual void upgradeBuildings2() = 0;
	virtual void printInformation(int buildingNumber, std::array<int, 5> requiredResources, std::vector<std::string> buildingLetterList) = 0;
	/*double requiredResourcesBuildings[6][5] = {
		{1, 0.5, 0.25, 0.125, 0.0625},
		{2, 1, 0.5, 0.25, 0.125},
		{3, 2, 1, 0.5, 0.25},
		{4, 3, 2, 1, 0.5},
		{5, 4, 3, 2, 1},
		{1, 1, 1, 1, 0.2} };*/
	/*double requiredResourcesFarm [5] = {1, 0.5, 0.25, 0.125, 0.0625};
   double requiredResourcesLumberMill [5] = {2, 1, 0.5, 0.25, 0.125};
   double requiredResourcesQuarry [5] = {3, 2, 1, 0.5, 0.25};
   double requiredResourcesMine [5] = {4, 3, 2, 1, 0.5};
   double requiredResourcesChurch [5] = {5, 4, 3, 2, 1};
   double requiredResourcesBarracks [5] = {1, 1, 1, 1, 0.2};*/
};

#endif