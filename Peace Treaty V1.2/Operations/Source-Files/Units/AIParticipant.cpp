#include <math.h>

#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include AIPARTICIPANTS_HEADER

using namespace PROV;

provSPTR AIParticipants::pickRandomProvince() {
	int randomNum = rand() & Provinces::Vector.size();
	return Provinces::Vector.at(randomNum); 
}