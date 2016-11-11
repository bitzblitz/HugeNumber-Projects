using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using HugeNumbers;

namespace HugeNumberTest
	{
	[TestClass]
	public class HugeNumberTests
		{
		[TestMethod]
		public void TestPositiveIntegerConstrucor()
			{
			HugeNumber result = new HugeNumber(12);
			HugeNumber expected = new HugeNumber() { false, false, true, true, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of 12");
			result = new HugeNumber(11);
			expected = new HugeNumber() { true, true, true, true, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of 11");
			result = new HugeNumber(13);
			expected = new HugeNumber() { true, false, true, true, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of 13");
			result = new HugeNumber(15);
			expected = new HugeNumber() { true, true, false, false, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of 15");
			}

		[TestMethod]
		public void TestNegativeIntegerConstrucor()
			{
			HugeNumber result = new HugeNumber(-12);
			HugeNumber expected = new HugeNumber() { false, false, true, false, true, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of -12.");
			result = new HugeNumber(-11);
			expected = new HugeNumber() { true, false, true, false, true, true };
			CollectionAssert.AreEqual(expected, result,"Failed on conversion of -11.");
			}

		[TestMethod]
		public void TestCopyConstructor()
			{
			HugeNumber original = new HugeNumber() { true, false, true, false, true, true };
			HugeNumber copy = new HugeNumber(original);
			CollectionAssert.AreEqual(original, copy, "Copy constructor failed.");
			}

		[TestMethod]
		public void TestToInt()
			{
			HugeNumber result = new HugeNumber() { true, true, false, false, true };
			long expected = 15;
			Assert.AreEqual(expected, result.ToLong(), "ToLong failed for 15.");
			result = new HugeNumber() { true, false, true, false, true, true };
			expected = -11;
			Assert.AreEqual(expected, result.ToLong(), "ToLong failed for 15.");
			}

		[TestMethod]
		public void TestToString()
			{
			HugeNumber result = new HugeNumber() { true, true, false, false, true };
			string expected = "11001";
			Assert.AreEqual(expected, result.ToString(), "ToString failed for 15.");
			result = new HugeNumber() { true, false, true, false, true, true };
			expected = "101011";
			Assert.AreEqual(expected, result.ToString(), "ToString failed for -11.");
			}

		[TestMethod]
		public void TestNegate()
			{
			HugeNumber input = new HugeNumber() { true, true, false, false, true };	// 15
			HugeNumber expected = new HugeNumber() { true, false, false, false, true, true }; // -15
			HugeNumber result = input.Negate();
			CollectionAssert.AreEqual(expected, result, "Failed on negate of 15.");
			CollectionAssert.AreEqual(input, result.Negate(), "Failed on negate of -15.");
			}

		[TestMethod]
		public void TestCompare()
			{
			HugeNumber eleven = new HugeNumber() { true, true, true, true, true };
			HugeNumber twelve = new HugeNumber() { false, false, true, true, true };
			HugeNumber thirteen = new HugeNumber() { true, false, true, true, true };
			Assert.AreEqual(1, twelve.CompareTo(eleven), "Compare 12 > 11 failed.");
			Assert.AreEqual(0, twelve.CompareTo(twelve), "Compare 12 == 12 failed.");
			Assert.AreEqual(-1, twelve.CompareTo(thirteen), "Compare 12 < 13 failed.");
			HugeNumber sixtyfour = new HugeNumber() { false, false, false, false, false, false, true };
			Assert.AreEqual(-1, twelve.CompareTo(sixtyfour), "Compare 12 < 64 failed.");
			HugeNumber five = new HugeNumber() { true, false, true };
			Assert.AreEqual(1, twelve.CompareTo(five), "Compare 12 > 5 failed.");
			HugeNumber minus_fifteen = new HugeNumber() { true, false, false, false, true, true }; // -15
			Assert.AreEqual(1, twelve.CompareTo(minus_fifteen), "Compare 12 > -15 failed.");
			Assert.AreEqual(-1,minus_fifteen.CompareTo( twelve), "Compare -15 < 12 failed.");
			Assert.IsTrue(twelve > eleven, "Compare 12 > 11 failed.");
			Assert.IsFalse(eleven > twelve , "Compare 11 < 12 failed.");
			Assert.IsFalse(twelve < eleven, "Compare 12 > 11 failed.");
			Assert.IsTrue(eleven < twelve , "Compare 11 < 12 failed.");
			Assert.IsTrue(twelve == twelve , "Compare 12 == 12 failed.");
			Assert.IsTrue(twelve <= twelve , "Compare 12 <= 12 failed.");
			Assert.IsFalse(twelve <= eleven , "Compare 12 <= 11 failed.");
			Assert.IsTrue(twelve >= twelve , "Compare 12 <= 12 failed.");
			Assert.IsTrue(twelve >= eleven , "Compare 12 <= 11 failed.");
			}

		[TestMethod]
		public void TestAdd()
			{
			HugeNumber eleven = new HugeNumber() { true, true, true, true, true };
			HugeNumber twelve = new HugeNumber() { false, false, true, true, true };
			HugeNumber thirteen = new HugeNumber() { true, false, true, true, true };
			HugeNumber twentythree = new HugeNumber { true, true, false, true, false, true, true };
			HugeNumber minus_twentythree = twentythree.Negate();
			CollectionAssert.AreEqual(twentythree, eleven + twelve, "Add failed 11+12.");
			CollectionAssert.AreEqual(twentythree, twelve + eleven, "Add failed 12+11.");
			CollectionAssert.AreEqual(new HugeNumber() { true }, twelve + eleven.Negate(), "Add failed 12+-11.");
			CollectionAssert.AreEqual(new HugeNumber() {  }, twentythree + minus_twentythree, "Add failed 23+-23.");
			}

		[TestMethod]
		public void TestSubtract()
			{
			HugeNumber eleven = new HugeNumber() { true, true, true, true, true };
			HugeNumber twelve = new HugeNumber() { false, false, true, true, true };
			HugeNumber thirteen = new HugeNumber() { true, false, true, true, true };
			HugeNumber one = new HugeNumber { true};
			CollectionAssert.AreEqual(one.Negate(), eleven - twelve, "Add failed 11-12.");
			CollectionAssert.AreEqual(one, twelve - eleven, "Add failed 12-11.");
			HugeNumber twentythree = new HugeNumber { true, true, false, true, false, true, true };
			CollectionAssert.AreEqual(twentythree, twelve - eleven.Negate(), "Add failed 12--11.");
			}
		}
	}
