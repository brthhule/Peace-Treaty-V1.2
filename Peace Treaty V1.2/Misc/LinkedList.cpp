#include "LinkedList.h"

LinkedList::LinkedList()
{
	OF::debugFunction("LinkedList, LinkedList (0)");
	head = NULL;
	tail = NULL;
	provincesNum = 0;
}

void LinkedList::LLupdateprovinceResources()
{
	OF::debugFunction("LinkedList, LLupdateProvinceResources");
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
	OF::debugFunction("LinkedList, getProvincesNum");
	return provincesNum;
}

void LinkedList::addNode (Provinces &provinceArg)
{
	OF::debugFunction("LinkedList, addNode");
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



std::vector<Provinces> *LinkedList::createMap (int size)
{
	OF::debugFunction("LinkedList, createMap");
	std::cout << "LLCreate Map...\n";
	provincesList.clear();//Fix this so don't need to clear every time createMap is called.
	//std::unordered_map<std::string, Provinces> provincesList;
	for (int x = 0; x < size * size; x++)
	{
		Provinces newProvince (x);
		newProvince.setkingdomname("EMPTY");
		addNode(newProvince);
		//std::pair<std::string, Provinces> newValue(newProvince.getProvinceName(), newProvince);
		provincesList.push_back(newProvince);
	}
	return &provincesList;
}


}