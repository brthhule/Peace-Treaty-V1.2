#include <iostream>


#include "..\..\..\Support\Paths.h"
#include PARTICIPANTS_HEADER 
#include PROVINCES_HEADER
#include COMMANDERS_HEADER

class AIParticipants : Participants { 
public:
	PROV::provSPTR pickRandomProvince(); 

private:
};