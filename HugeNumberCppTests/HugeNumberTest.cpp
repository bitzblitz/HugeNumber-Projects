#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\HugeNumberLib\HugeNumberLib.h"
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HugeNumberCppTests
	{
	TEST_CLASS(UnitTest1)
		{
		protected:
			void AreEqual(HugeNumber A, HugeNumber B, const wchar_t* Message=nullptr, const __LineInfo* pLineInfo=NULL)
				{
				Assert::AreEqual(A.size(),B.size(), Message, pLineInfo);
				if(A.size()!=B.size())
					throw length_error("Bit lengths are unequal.");
				for(auto a=A.begin(), b=B.begin();a<A.end();++a, ++b)
					{
					Assert::IsTrue(*a == *b, Message, pLineInfo);
					}
				}

		public:

			TEST_METHOD(ConversionToIntTest)
				{
				HugeNumber a={true, false, false, true, true, true};
				int expected=-23;
				Assert::AreEqual(expected, static_cast<int>(a), L"Conversion to long long failed.", LINE_INFO());
				}

			TEST_METHOD(ConversionFromIntTest)
				{
				while(long long n=2<numeric_limits<int>::max()*numeric_limits<int>::max())
					{
					HugeNumber x(n);
					AreEqual(x.ToInt(), n, L"Conversion from int failed",LINE_INFO());
					}
				}

			TEST_METHOD(ConstructionTest)
				{
				HugeNumber a(23);
				HugeNumber b={true, true, false, true, false, true, true};
				AreEqual(a, b, L"Construction from 23 failed",LINE_INFO());
				char bit_str[]="101011";
				HugeNumber c=bit_str;
				HugeNumber d={true, false, true, false, true, true};
				AreEqual(c, d, L"Construction from char* failed.",LINE_INFO());
				HugeNumber e=string(bit_str);
				AreEqual(e, d, L"Construction from string failed.",LINE_INFO());
				HugeNumber f(c);
				AreEqual(f, d, L"Copy constructor failed.",LINE_INFO());
				HugeNumber g={1, 1, 0, 1, 0, 1, 1};
				AreEqual(g, b, L"Creation from array of ints failed", LINE_INFO());
				}

			TEST_METHOD(NegationTest)
				{
				HugeNumber x(numeric_limits<int>::max());
				Assert::AreEqual(-numeric_limits<int>::max(), static_cast<int>(x.Negate()), L"Negation failed.", LINE_INFO());
				Assert::AreEqual(-numeric_limits<int>::max(), static_cast<int>(-x), L"Negation failed.", LINE_INFO());
				srand(23);
				HugeNumber y;
				for(int i=0;i < 100;++i)
					{
					int a=rand()*rand();
					y=a;
					Assert::AreEqual(-a, static_cast<int>(-y), L"Negation failed.", LINE_INFO());
					}
				}

			TEST_METHOD(AdditionTest)
				{
				srand(23);
				for(int i = 0;i < 100;++i)
					{
					int a=rand();
					int b=rand()*rand();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x+y;
					Assert::AreEqual(a+b, static_cast<int>(z), L"Addition failed.", LINE_INFO());
					Assert::AreEqual(a+b, static_cast<int>(y+x), L"Addition failed.", LINE_INFO());
					}
				for(int i = 0;i < 1000;++i)
					{	// big numbers
					long long a=rand()*numeric_limits<int>::max();
					long long b=rand()*rand()*numeric_limits<int>::max();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x+y;
					wstringstream msg;
					msg<<L"Addition with "<<a<<L" and "<<b<<L" failed.";
					Assert::AreEqual(0, static_cast<int>(static_cast<long long>(z)-(a+b)), msg.str().c_str(), LINE_INFO());
					}
				for(int i = 0;i < 100;++i)
					{
					int a=-rand();	// test with negatives
					int b=rand()*rand();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x+y;
					Assert::AreEqual(a+b, static_cast<int>(z), L"Addition with negatives failed.", LINE_INFO());
					Assert::AreEqual(a+b, static_cast<int>(y+x), L"Addition with negatives failed.", LINE_INFO());
					}
				int v=rand();
				HugeNumber x(v);
				Assert::AreEqual(0, static_cast<int>(x+-x), L"Addition to 0 failed.", LINE_INFO());
				}

			TEST_METHOD(SubtractionTest)
				{
				srand(23);
				for(int i = 0;i < 100;++i)
					{
					int a=rand();
					int b=rand()*rand();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x-y;
					Assert::AreEqual(a-b, static_cast<int>(z), L"Subtraction failed.", LINE_INFO());
					}
				for(int i=0;i < 100;++i)
					{	// big numbers
					long long a=rand()*numeric_limits<int>::max();
					long long b=rand()*rand()*numeric_limits<int>::max();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x-y;
					Assert::AreEqual(0, static_cast<int>(static_cast<long long>(z)-(a-b)), L"Addition failed.", LINE_INFO());
					}
				for(int i = 0;i < 100;++i)
					{
					int a=-rand();	// test with negatives
					int b=rand()*rand();
					HugeNumber x(a);
					HugeNumber y(b);
					HugeNumber z=x-y;
					Assert::AreEqual(a-b, static_cast<int>(z), L"Subtraction failed.", LINE_INFO());
					}
				int v=rand();
				HugeNumber x(v);
				Assert::AreEqual(0, static_cast<int>(x-x), L"Subtraction to 0 failed.", LINE_INFO());
				}

			TEST_METHOD(ComaprisonTest)
				{
				HugeNumber tiny(numeric_limits<int>::min());
				HugeNumber small(20);
				HugeNumber medium(23);
				HugeNumber same(23);
				HugeNumber large(24);
				HugeNumber huge(numeric_limits<int>::max());
				HugeNumber less_than_huge(numeric_limits<int>::max()-1);
				HugeNumber zero;
				Assert::IsTrue(small.CompareTo(medium)<0, L"CompareTo small < medium failed", LINE_INFO());
				Assert::IsTrue(small<medium, L"operator < failed TRUE.", LINE_INFO());
				Assert::IsFalse(small>medium||medium>large, L"operator < failed FALSE", LINE_INFO());
				Assert::IsTrue(medium>=small, L"operator >= failed TRUE", LINE_INFO());
				Assert::IsFalse(small>=medium||medium>=large, L"operator >= failed FALSE", LINE_INFO());
				Assert::IsFalse(small==medium||small==large||medium==large||large==small, L"operator == fails FALSE", LINE_INFO());
				Assert::IsTrue(same==medium, L"operator == fails TRUE", LINE_INFO());
				Assert::IsTrue(tiny<small, L"tiny < small failed TRUE", LINE_INFO());
				Assert::IsTrue(less_than_huge<huge, L"less_than_huge < huge failed TRUE", LINE_INFO());
				Assert::IsTrue(huge==huge, L"huge == huge failed TRUE", LINE_INFO());
				Assert::IsTrue(zero==zero, L"zero == zero failed TRUE", LINE_INFO());
				Assert::IsTrue(tiny<=zero, L"tiny <= zero failed TRUE", LINE_INFO());
				Assert::IsTrue(huge>zero, L"huge > zero failed TRUE", LINE_INFO());
				}
		};
	}