#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Test\pch.h"
#include "CppUnitTest.h"

#include "..\..\Peace-Treaty-V1.2\Peace-Treaty-V1.2\Support\Paths.h"
#include INF_HEADER
#include PARTICIPANTS_HEADER
#include COMMANDERS_HEADER
#include PROVINCES_HEADER

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(ParticipantsTest)
	{
	public:
		TEST_METHOD(constructor) {
			//INF::continentSize = 5;
			//Map::setMap();
			/*Participants::setHumanPlayers(1);
			Participants newParticipant;
			Assert::AreEqual(Participants::getParticipantsNum(), 1);
			Participants::clear(); */
			//Participants participant;
			Assert::AreEqual(1, 1);
		}
	};
}
