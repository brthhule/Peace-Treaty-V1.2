#include "pch.h"
#include "CppUnitTest.h"

#include "../InfrastructureThing/Infrastructure.h"
#include "../Peace Treaty V1.2/Misc/CV.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PeaceTreatyTest2
{
	TEST_CLASS(MainTest)
	{
	public:
		
		TEST_METHOD(Test1)
		{
			Assert::AreEqual(4, 4);
		}

		TEST_METHOD(printPersonTest) {
			Assert::AreEqual(4, 5);
		}

		TEST_METHOD(test1) {
			Assert::AreNotEqual(4, 5);
		}
	};
}
