#ifndef BASE_H
#define BASE_H

/*Underlying class that all other classes derive from. Similar to the Object class in Java*/
class BASE {
public:
	BASE();
	bool getNullCondition();
	void setNullCondition(bool nullConditionArg);
private:
	bool nullCondition;
};

#endif

