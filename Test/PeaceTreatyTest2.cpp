#include "..\Test\pch.h"
#include "CppUnitTest.h"

#include "../Peace-Treaty-V1.2/Support/Paths.h"
#include "../Peace-Treaty-V1.2/Operations/Header-Files/Units/Provinces/Buildings/BuildingsBASE.h"
#include "../Peace-Treaty-V1.2/Operations/Header-Files/Units/Provinces/Provinces.h"
#include INF_HEADER

using namespace Microsoft::VisualStudio::CppUnitTestFramework;  

namespace Test 
{
	TEST_CLASS(MainTest)
	{
	public:
		
		TEST_METHOD(Test1) 
		{
			Assert::AreEqual(4, 4); 
		}

		TEST_METHOD(printPersonTest) {
			Assert::AreNotEqual(4, 5);
		}

		TEST_METHOD(test1) {
			Assert::AreNotEqual(4, 5);
		}
	};

	TEST_CLASS(BuildingsVector) {

	};
}
