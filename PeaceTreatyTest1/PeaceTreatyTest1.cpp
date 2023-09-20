#include "pch.h"
#include "CppUnitTest.h"
#include "../Infrastructure/Methods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PeaceTreatyTest1
{
	TEST_CLASS(PeaceTreatyTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(2, Add(2, 2));
		}
	};
}
