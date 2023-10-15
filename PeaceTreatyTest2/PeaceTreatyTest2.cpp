#include "pch.h"
#include "CppUnitTest.h"

#include "../InfrastructureThing/Infrastructure.h"
#include "../Peace Treaty V1.2/Misc/ConstValues.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PeaceTreatyTest2
{
	TEST_CLASS(PeaceTreatyTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(4, Add(2, 2));
		}

		TEST_METHOD(printPersonTest) {
			CV::printPerson();
		}
	};
}
