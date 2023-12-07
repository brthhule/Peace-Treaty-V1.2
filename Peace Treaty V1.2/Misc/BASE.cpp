#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Misc\BASE.h"

BASE::BASE() {
	nullCondition = false;
}

bool BASE::getNullCondition() {
	return nullCondition;
}

void BASE::setNullCondition(bool nullConditionArg) {
	nullCondition = nullConditionArg;
}