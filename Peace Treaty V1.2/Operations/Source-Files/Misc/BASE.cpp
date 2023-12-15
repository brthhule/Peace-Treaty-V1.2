#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
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