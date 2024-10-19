#include "..\..\..\Support\Paths.h"
#include BASE_HEADER

BASE::BASE() {
	nullCondition = false;
}

bool BASE::getNullCondition() {
	return nullCondition;
}

void BASE::setNullCondition(bool nullConditionArg) {
	nullCondition = nullConditionArg;
}

void BASE::nothing() {

}