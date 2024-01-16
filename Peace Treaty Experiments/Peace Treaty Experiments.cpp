// Peace Treaty Experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

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

class Provinces {
public:
    using String = std::string;

    Provinces(std::string name) {
        this->name = name;
    }
    const std::string& getName() {
        return name;
    }


private:
    std::string name;
};

namespace PROV {
    using provSPTR = std::shared_ptr<Provinces>;
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

int main() {
    std::unique_ptr<Provinces> thing (new Provinces("hey"));
    std::unique_ptr<Provinces> replacement(new Provinces("foo"));

    std::cout << thing->getName() << "\n";

    thing.swap(replacement);

    Provinces &province_ptr = *replacement.get();
    replacement.release();

    std::cout << province_ptr.getName() << "\n";

    std::unique_ptr<Provinces> returnProvince(&province_ptr);

    thing.swap(returnProvince);
    std::cout << thing->getName() << "\n";
    
    return 0;
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
