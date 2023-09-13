#include "LinkedList.h"

LinkedList::LinkedList()
{
	OF.debugFunction("LinkedList, LinkedList (0)");
	head = NULL;
	tail = NULL;
	provincesNum = 0;
}

void LinkedList::LLupdateprovinceResources()
{
	OF.debugFunction("LinkedList, LLupdateProvinceResources");
	node *temp;
	temp = head;
	while (temp != NULL)
	{
		temp->province->updateBuildingsProduction();
		temp->province->updateProvinceResources();
		temp = temp->next;
	}
}

int LinkedList::getProvincesNum ()
{
	OF.debugFunction("LinkedList, getProvincesNum");
	return provincesNum;
}

void LinkedList::addNode (Provinces &provinceArg)
{
	OF.debugFunction("LinkedList, addNode");
	node *temp = new node;
	temp->province = &provinceArg;
	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = tail->next;
	}
	provincesNum ++;
}

Provinces* LinkedList::getProvinceByNum (int num)
{
	OF.debugFunction("LinkedList, getProvinceByNum");
	std::cout << "GetProvinceByNum\n";
	std::cout << "Num: " << num << std::endl;
	
	node *temp;
	temp = head;
	while (temp != NULL)
	{
		std::cout << "temp->province->getLLN: " << temp->province->getLinkedListNumber() << std::endl;
		if (temp->province->getLinkedListNumber() == num)
		{
			return temp->province;
		}
	}

	std::cout << "Error path... \n";
	Provinces newProvince;
	return &newProvince;
}

std::unordered_map<std::string, Provinces*> LinkedList::createMap (int size)
{
	OF.debugFunction("LinkedList, createMap");
	std::cout << "LLCreate Map...\n";
	std::unordered_map<std::string, Provinces*> provincesList;
	for (int x = 0; x < size * size; x++)
	{
		Provinces newProvince (x);
		addNode(newProvince);
		allProvinces.push_back(&newProvince);
	}
	return allProvinces;
}

void LinkedList::listProvinces()
{
	OF.debugFunction("LinkedList, listProvinces");
	node *temp;
	temp = head;
	int a = 1;
	while (temp != NULL)
	{
		std::cout << a << ") ";
		std::cout << "Province Name: " << temp->province->getUnitName() << std::endl;
		std::cout << "Province number: " << temp->province->getLinkedListNumber() << std::endl;
		temp = temp->next;
		a++;
	}
}