// Peace Treaty Experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "../Peace Treaty V1.2/Operations/Header-Files/Units/Provinces::/Buildings/BuildingsBASE.h"
#include "../Peace Treaty V1.2/Operations/Header-Files/Units/Provinces::/Buildings/Resources/Farm.h"

template<class T>
class sPTR {
public:
    sPTR<T>(T thing) {
        ptr = std::make_shared<T>(thing); 
    }
    std::shared_ptr<T> get() {
        return ptr;
    }
private:
    std::shared_ptr<T> ptr;
};

class Commanders {
public:
    Commanders(std::string name) {
        this->name = name;
    }
    std::string getName() {
        return name;
    }
private:
    std::string name;
};

class Provinces:: {
public:
    using String = std::string;

    Provinces::(std::string name) {
        this->name = name;
    }
    const std::string& getName() {
        return name;
    }

    Provinces::& operator+=(const std::shared_ptr<Commanders> rhs){
        commanderList.push_back(rhs); 
        return *this; // return the result by reference
    }

    int getCommanderListSize() {
        return commanderList.size();
    }

    void printCommanderName(int index) {
        std::cout << commanderList.at(index)->getName() + "\n";
    }


private:
    std::string name;
    std::vector<std::shared_ptr<Commanders>>commanderList;
};

namespace PROV {
    using provSPTR = std::shared_ptr<Provinces::>;
}
/*
class Commanders {
public:
    Provinces::String myString;  
    Commanders(std::string name) {
        this->name = name;
    }

    decltype(myString) getName() {   
        return name;
    }
private:
    decltype(myString) name; 
};*/

class foo {
public:
    foo() {
        std::string name = "Hey";
        province.reset(new Provinces::(name));
    };
    Provinces::& getProvince() {
        return *province.get();
    }
    std::string getName() {
        return province->getName();
    }
private:
    std::unique_ptr<Provinces::> province;
};

int main() {
    
    std::vector<std::unique_ptr<BuildingsBASE>> buildingsVector;

    buildingsVector.push_back(std::move(std::unique_ptr<BuildingsBASE>(new Farm())));  

    //std::cout << buildingsVector.at(0)->getLevel();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
