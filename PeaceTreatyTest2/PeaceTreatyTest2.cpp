#include "pch.h"
#include "CppUnitTest.h"

#include "../InfrastructureThing/Infrastructure.h"

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
	};
}
