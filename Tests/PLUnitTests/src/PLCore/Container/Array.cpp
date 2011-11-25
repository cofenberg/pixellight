//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Array.h>
#include <PLCore/Container/Container.h>

#include <iostream>

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Array_PrimitiveChar) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	Array<char> Arr;

	TEST(SetResizeCount_Zero) {
		CHECK_EQUAL(10U, Arr.GetResizeCount());

		Arr.SetResizeCount(0U);
		CHECK_EQUAL(0U, Arr.GetResizeCount());
	}

	TEST(SetResizeCount_100) {
		Arr.SetResizeCount(100U);
		CHECK_EQUAL(100U, Arr.GetResizeCount());
	}	

	TEST(SetResizeCount_4byte) {
		Arr.SetResizeCount(4294967295U);
		CHECK_EQUAL(4294967295U, Arr.GetResizeCount());

		Arr.SetResizeCount(10U);
		CHECK_EQUAL(10U, Arr.GetResizeCount());
	}

	TEST(Reset) {
		Arr.Reset();
		CHECK_EQUAL(0U, Arr.GetNumOfElements());

		Arr.Add();
		Arr.Reset();
		CHECK_EQUAL(0U, Arr.GetNumOfElements());
	}

	TEST(Resize) {
		// TODO: implement
	}

	/*
	 * general container functions 
	 *
	 */

	TEST(isEmpty_and_Clear) {
		Arr.Clear();
		CHECK(Arr.IsEmpty());
		CHECK_EQUAL(0U, Arr.GetNumOfElements());
		CHECK_EQUAL(0U, Arr.GetMaxNumOfElements());

		Arr.Add();
		CHECK(!Arr.IsEmpty());
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL(Arr.GetResizeCount(), Arr.GetMaxNumOfElements());
	}

	TEST(IsElement_Within) {
		Arr.Reset();
		Arr.Add('4');
		CHECK(Arr.IsElement('4'));
	}

	TEST(IsElement_NotWithin) {
		Arr.Reset();
		Arr.Add('6');
		CHECK(!Arr.IsElement('4'));
	}

	TEST(GetIndex_ElementWithin) {
		Arr.Reset();
		Arr.Add('4');
		CHECK_EQUAL(0, Arr.GetIndex('4'));
	}

	TEST(GetIndex_ElementNotWithin) {
		Arr.Reset();
		Arr.Add('6');
		CHECK(Arr.GetIndex('4')<0);
	}

	TEST(Get_Within_Bounds) {
		Arr.Clear();
		Arr.Add('6');
		Arr.Add('4');

		CHECK_EQUAL('4', Arr.Get(1U));
	}

	TEST(Get_Outside_Bounds) {
		Arr.Clear();
		Arr.Add('4');

		CHECK_EQUAL(NULL, Arr.Get(6U));
	}

	TEST(Operator_AccessElement_Within_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');

		CHECK_EQUAL('1', Arr[0U]);
		CHECK_EQUAL('2', Arr[1U]);
	}

	TEST(Operator_AccessElement_Outside_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');

		CHECK_EQUAL(NULL, Arr[5U]);
	}

	TEST(Replace_ElementWithin) {
		Arr.Reset();
		Arr.Add('1');
		Arr.Add('2');

		CHECK(Arr.Replace('2', '0'));
		CHECK_EQUAL('0', Arr[1]);
	}

	TEST(Replace_ElementNotWithin) {
		Arr.Reset();
		Arr.Add('1');
		Arr.Add('2');

		CHECK(!Arr.Replace('4', '0'));
		CHECK_EQUAL('2', Arr[1]);
	}

	TEST(ReplaceAtIndex_Within_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');

		CHECK(Arr.ReplaceAtIndex(1U, '0'));
		CHECK_EQUAL('0', Arr[1U]);
	}

	TEST(ReplaceAtIndex_Outside_Bounds_Positive) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');

		CHECK(!Arr.ReplaceAtIndex(5U, '0'));
		CHECK_EQUAL('2', Arr[1U]);
	}

	TEST(Add_NoPassedElement) {
		Arr.Clear();

		// we can't check this as we don't know what the element will be initialized with, e.g. if it is initialized with 0 a CHECK() will fail but will be ok otherwise!
		Arr.Add();
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		Arr.Add();
		CHECK_EQUAL(2U, Arr.GetNumOfElements());
	}

	TEST(Add_NoPassedElement_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);

		CHECK_EQUAL(Array<char>::Null, Arr.Add());

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Add_Element) {
		Arr.Clear();

		CHECK_EQUAL('1', Arr.Add('1'));
		CHECK_EQUAL('2', Arr.Add('2'));

		CHECK_EQUAL(2U, Arr.GetNumOfElements());
		CHECK_EQUAL(Arr.GetResizeCount(), Arr.GetMaxNumOfElements());
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('2', Arr.Get(1U));
	}

	TEST(Add_Element_NoResize) {
		Arr.SetResizeCount(0U);
		Arr.Clear();
		Arr.Resize(0U, false);

		CHECK_EQUAL(Array<char>::Null, Arr.Add('1'));

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Add_C_Array) {
		Arr.Clear();
		char cArr[] = {'a', 'b', 'c', 'd'};

		// append
		CHECK_EQUAL(4U, Arr.Add(cArr, 4U));

		CHECK_EQUAL(4U, Arr.GetNumOfElements());
		CHECK_EQUAL('a', Arr.Get(0U));
		CHECK_EQUAL('b', Arr.Get(1U));
		CHECK_EQUAL('c', Arr.Get(2U));
		CHECK_EQUAL('d', Arr.Get(3U));
		CHECK_EQUAL(NULL, Arr.Get(4U));

		// append
		CHECK_EQUAL(2U, Arr.Add(cArr, 2));

		CHECK_EQUAL(6U, Arr.GetNumOfElements());
		CHECK_EQUAL('a', Arr.Get(0U));
		CHECK_EQUAL('b', Arr.Get(1U));
		CHECK_EQUAL('c', Arr.Get(2U));
		CHECK_EQUAL('d', Arr.Get(3U));
		CHECK_EQUAL('a', Arr.Get(4U));
		CHECK_EQUAL('b', Arr.Get(5U));
		CHECK_EQUAL(NULL, Arr.Get(6U));
	}

	TEST(Add_C_Array_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(2U, false);
		char cArr[] = {'a', 'b', 'c', 'd'};

		CHECK_EQUAL(2U, Arr.Add(cArr, 4U));
		CHECK_EQUAL(0U, Arr.Add(cArr, 2U));

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Operator_Add_Element) {
		Arr.Clear();
		Arr += 'a';

		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL('a', Arr.Get(0U));
		CHECK_EQUAL(NULL, Arr.Get(1U));

		Arr += 'b';

		CHECK_EQUAL(2U, Arr.GetNumOfElements());
		CHECK_EQUAL('a', Arr.Get(0U));
		CHECK_EQUAL('b', Arr.Get(1U));
	}

	TEST(Operator_Add_Element_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr += 'a';

		CHECK_EQUAL(0U, Arr.GetNumOfElements());
		CHECK_EQUAL(0U, Arr.GetMaxNumOfElements());

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Add_Container) {
		Arr.Clear();

		// constructing container for adding
		Array<char> AppendArr;
		AppendArr.Add('1');
		AppendArr.Add('2');
		AppendArr.Add('3');
		AppendArr.Add('4');

		/*
		TODO: refactor these: each scenario = one TEST()

		SCENARIOS:			return value, description
		Add(Append, 0, 0);	true, all elements from index 0
		Add(Append, 0, 1);	true, element at index 0
		Add(Append, 0, 8);	true, all to index 8 (stops when all elements from appending arr are added)
		Add(Append, 2, 0);	true, all from index 2
		Add(Append, 2, 1);	true, element at index 2
		Add(Append, 2, 8);	true, all from index 2
		Add(Append, 9, 0);	false
		Add(Append, 9, 99);	false
		Add(Append);		same as Add(Append, 0, 0)
		*/

		// add all elements
		CHECK(Arr.Add(AppendArr, 0U, 0U));
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('2', Arr.Get(1U));
		CHECK_EQUAL('3', Arr.Get(2U));
		CHECK_EQUAL('4', Arr.Get(3U));

		// add element at index 0
		CHECK(Arr.Add(AppendArr, 0U, 1U));
		CHECK_EQUAL(5U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(4U));

		// add all elements
		CHECK(Arr.Add(AppendArr, 0U, 8U));
		CHECK_EQUAL(9U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(5U));
		CHECK_EQUAL('2', Arr.Get(6U));
		CHECK_EQUAL('3', Arr.Get(7U));
		CHECK_EQUAL('4', Arr.Get(8U));

		// add all elements from index 2
		CHECK(Arr.Add(AppendArr, 2U, 0U));
		CHECK_EQUAL(11U, Arr.GetNumOfElements());
		CHECK_EQUAL('3', Arr.Get(9U));
		CHECK_EQUAL('4', Arr.Get(10U));

		// add element at index 2
		CHECK(Arr.Add(AppendArr, 2U, 1U));
		CHECK_EQUAL(12U, Arr.GetNumOfElements());
		CHECK_EQUAL('3', Arr.Get(11U));

		// add all elements from index 2 to 8 (stops when all elements of AppendArr are added)
		CHECK(Arr.Add(AppendArr, 2U, 8U));
		CHECK_EQUAL(14U, Arr.GetNumOfElements());
		CHECK_EQUAL('3', Arr.Get(12U));
		CHECK_EQUAL('4', Arr.Get(13U));

		// add no elements :)
		CHECK(!Arr.Add(AppendArr, 9U, 0U));
		CHECK_EQUAL(14U, Arr.GetNumOfElements());

		// add no elements :)
		CHECK(!Arr.Add(AppendArr, 9U, 99U));
		CHECK_EQUAL(14U, Arr.GetNumOfElements());

		// add all elements
		CHECK(Arr.Add(AppendArr));
		CHECK_EQUAL(18U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(14U));
		CHECK_EQUAL('2', Arr.Get(15U));
		CHECK_EQUAL('3', Arr.Get(16U));
		CHECK_EQUAL('4', Arr.Get(17U));
	}

	TEST(Add_Container_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(2, false);

		// constructing container for adding
		Array<char> AppendArr;
		AppendArr.Add('1');
		AppendArr.Add('2');
		AppendArr.Add('3');
		AppendArr.Add('4');

		// returns false, but inserts elements until Arr is full
		CHECK(!Arr.Add(AppendArr, 0U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());

		CHECK(!Arr.Add(AppendArr, 0U, 2U));

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Operator_Add_Container) {
		Arr.Clear();

		// constructing container for adding
		Array<char> AppendArr;
		AppendArr.Add('1');
		AppendArr.Add('2');
		AppendArr.Add('3');
		AppendArr.Add('4');

		Arr += AppendArr;

		CHECK_EQUAL(4U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('2', Arr.Get(1U));
		CHECK_EQUAL('3', Arr.Get(2U));
		CHECK_EQUAL('4', Arr.Get(3U));
	}

	TEST(Operator_Add_Container_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(2U, false, false);

		// constructing container for adding
		Array<char> AppendArr;
		AppendArr.Add('1');
		AppendArr.Add('2');
		AppendArr.Add('3');
		AppendArr.Add('4');

		// adds elements until Arr is full
		Arr += AppendArr;
		CHECK_EQUAL(2U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('2', Arr.Get(1U));

		// no elements added, Arr is full
		Arr+=AppendArr;
		CHECK_EQUAL(2U, Arr.GetNumOfElements());

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(AddAtIndex_Within_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// "copies" element that is at index
		// TODO: AddAtIndex(index) returns inserted element while AddAtIndex(value, index) returns true/false... intended?
		CHECK_EQUAL('3', Arr.AddAtIndex(2U));
		CHECK_EQUAL('3', Arr.Get(2U));
		CHECK_EQUAL(5U, Arr.GetNumOfElements());
	}

	TEST(AddAtIndex_Outside_Bounds_Positive) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK_EQUAL(Array<char>::Null, Arr.AddAtIndex(99));
	}

	TEST(AddAtIndex_Outside_Bounds_Negative) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// should append at the end of container, element not initialized! e.g. we can't check its value
		CHECK(Arr.AddAtIndex(-10));
		CHECK_EQUAL(5U, Arr.GetNumOfElements());
		CHECK(Arr.Get(Arr.GetNumOfElements()-1));
	}

	TEST(AddAtIndex_Within_Bounds_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(4, false, false);
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK_EQUAL(Array<char>::Null, Arr.AddAtIndex(2));
		CHECK_EQUAL('3', Arr.Get(2U));

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(AddAtIndex_Element_Within_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// "copies" element that is at index
		CHECK(Arr.AddAtIndex('x', 2));
		CHECK_EQUAL('x', Arr.Get(2U));
		CHECK_EQUAL(5U, Arr.GetNumOfElements());
	}

	TEST(AddAtIndex_Element_Outside_Bounds_Positive) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK(!Arr.AddAtIndex('x', 99));
	}

	TEST(AddAtIndex_Element_Outside_Bounds_Negative) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// should append at the end of container
		CHECK(Arr.AddAtIndex('x', -10));
		CHECK_EQUAL(5U, Arr.GetNumOfElements());
		CHECK_EQUAL('x', Arr.Get(Arr.GetNumOfElements()-1));
	}

	TEST(AddAtIndex_Element_Within_Bounds_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(4U, false, false);
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK(!Arr.AddAtIndex('x', 2));
		CHECK_EQUAL('3', Arr.Get(2U));

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(AddAtIndex_Element_Outside_Bounds_Negative_NoResize) {
		Arr.Clear();
		Arr.SetResizeCount(0U);
		Arr.Resize(4, false, false);
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// should NOT append at the end of container
		CHECK(!Arr.AddAtIndex('x', -10));
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
	
		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Remove_Element_Within) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK(Arr.Remove('2'));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());
	}

	TEST(Remove_Element_NotWithin) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// should NOT append at the end of container
		CHECK(!Arr.Remove('9'));
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
	}

	TEST(RemoveAtIndex_Inside_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK(Arr.RemoveAtIndex(2U));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());
	}

	TEST(RemoveAtIndex_Outside_Bounds) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		CHECK(!Arr.RemoveAtIndex(99U));
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
	}

	TEST(RemoveAtIndex_Inside_Bounds_With_Resize) {
		Arr.Clear();
		Arr.SetResizeCount(1U);
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// check state of array
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
		CHECK_EQUAL(4U, Arr.GetMaxNumOfElements());

		// remove element and check number of elements again, should be one less now
		CHECK(Arr.RemoveAtIndex(1U));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());
		CHECK_EQUAL(3U, Arr.GetMaxNumOfElements());

		// set resizecount back to default
		Arr.SetResizeCount(10U);
	}

	TEST(Operator_Remove_Element_Within) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		Arr -= '2';

		CHECK_EQUAL('3', Arr.Get(1U));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());
	}

	TEST(Operator_Remove_Element_NotWithin) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		Arr -= '9';

		CHECK_EQUAL('2', Arr.Get(1U));
		CHECK_EQUAL(4U, Arr.GetNumOfElements());
	}

	TEST(Remove_Container) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		Array<char> RemoveArr;
		RemoveArr.Add('3');
		RemoveArr.Add('2');
		RemoveArr.Add('1');
		RemoveArr.Add('0');

		/*
		TODO: refactor these: each scenario = one TEST()

		SCENARIOS:			return value, description
		Remove(RemoveArr, 0, 0) true, all elements
		Remove(RemoveArr, 0, 1) true, element at index 0
		Remove(RemoveArr, 0, 8) true, all elements
		Remove(RemoveArr, 1, 0) true, elements from index 1 to end
		Remove(RemoveArr, 1, 1) true, element at index 1
		Remove(RemoveArr, 1, 8) true, elements from index 1 to 8 (stops at last element from RemoveArr)
		Remove(RemoveArr, 9, 0)	false
		Remove(RemoveArr, 9, 1) false
		Remove(RemoveArr, 9, 99) false
		Remove(RemoveArr)		same as Remove(RemoveArr, 0, 0)
		*/

		
		// all elements from index 0 to end
		CHECK(Arr.Remove(RemoveArr));
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL('4', Arr.Get(0U));

		
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// all elements in RemoveArr removed
		CHECK(Arr.Remove(RemoveArr, 0U, 0U));
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL('4', Arr.Get(0U));


		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// first element
		CHECK(Arr.Remove(RemoveArr, 0U, 1U));
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('2', Arr.Get(1U));
		CHECK_EQUAL('4', Arr.Get(2U));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());


		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// all elements from index 0 to 8
		CHECK(Arr.Remove(RemoveArr, 0U, 8U));
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL('4', Arr.Get(0U));


		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// all elements from index 1 to end
		CHECK(Arr.Remove(RemoveArr, 1U, 0U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());
		CHECK_EQUAL('3', Arr.Get(0U));
		CHECK_EQUAL('4', Arr.Get(1U));


		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// element at index 1
		CHECK(Arr.Remove(RemoveArr, 1U, 1U));
		CHECK_EQUAL(3U, Arr.GetNumOfElements());
		CHECK_EQUAL('1', Arr.Get(0U));
		CHECK_EQUAL('3', Arr.Get(1U));
		CHECK_EQUAL('4', Arr.Get(2U));

		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		// all elements from index 1 to 8 (stops at last element from RemoveArr)
		CHECK(Arr.Remove(RemoveArr, 1U, 8U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());
		CHECK_EQUAL('3', Arr.Get(0U));
		CHECK_EQUAL('4', Arr.Get(1U));

		// returns false (start index > number of elements)
		CHECK(!Arr.Remove(RemoveArr, 9U, 0U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());

		// returns false (start index > number of elements)
		CHECK(!Arr.Remove(RemoveArr, 9U, 1U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());

		// returns false (start index > number of elements)
		CHECK(!Arr.Remove(RemoveArr, 9U, 99U));
		CHECK_EQUAL(2U, Arr.GetNumOfElements());
	}

	TEST(Operator_Remove_Container) {
		Arr.Clear();
		Arr.Add('1');
		Arr.Add('2');
		Arr.Add('3');
		Arr.Add('4');

		Array<char> RemoveArr;
		RemoveArr.Add('3');
		RemoveArr.Add('2');
		RemoveArr.Add('1');
		RemoveArr.Add('0');

		Arr -= RemoveArr;
		CHECK_EQUAL(1U, Arr.GetNumOfElements());
		CHECK_EQUAL('4', Arr.Get(0U));
	}

	TEST(Copy) {
		Arr.Clear();

		Array<char> CopyArr, EmptyArr;
		CopyArr.Add('3');
		CopyArr.Add('2');
		CopyArr.Add('1');
		CopyArr.Add('0');

		/*
		TODO: refactor these: each scenario = one TEST()

		SCENARIOS:			return value, description
		Copy(CopyArr, 0, 0) true, all elements
		Copy(CopyArr, 0, 1) true, element at index 0
		Copy(CopyArr, 0, 8) true, all elements
		Copy(CopyArr, 1, 0) true, elements from index 1 to end
		Copy(CopyArr, 1, 1) true, element at index 1
		Copy(CopyArr, 1, 8) true, elements from index 1 to 8 (stops at last element of CopyArr)
		Copy(CopyArr, 9, 0)	false
		Copy(CopyArr, 9, 1) false
		Copy(CopyArr, 9, 99) false
		Copy(CopyArr)		same as Copy(CopyArr, 0, 0)
		Copy(EmptyArr)		false?
		*/

		// copies all elements from index 0 to end
		CHECK(Arr.Copy(CopyArr));
		CHECK(Arr.Compare(CopyArr));

		// copies all elements from index 0 to end
		CHECK(Arr.Copy(CopyArr, 0, 0));
		CHECK(Arr.Compare(CopyArr));

		// copies element at index 0
		CHECK(Arr.Copy(CopyArr, 0, 1));
		CHECK(Arr.Compare(CopyArr, 0, 1));

		// copies all elements
		CHECK(Arr.Copy(CopyArr, 0, 8));
		CHECK(Arr.Compare(CopyArr));

		// copies all elements from index 1 to end
		CHECK(Arr.Copy(CopyArr, 1, 0));
		CopyArr.RemoveAtIndex(1);
		CHECK(Arr.Compare(CopyArr, 1, 0));
		CopyArr.AddAtIndex('3', 0);

		// copies element at index 1
		CHECK(Arr.Copy(CopyArr, 1, 1));
		CopyArr.RemoveAtIndex(1);
		CHECK(Arr.Compare(CopyArr, 0, 1));
		CopyArr.AddAtIndex('3', 0);

		// copies all elements from index 1 to 8 (stops at last element of CopyArr)
		CHECK(Arr.Copy(CopyArr, 1, 8));
		CopyArr.RemoveAtIndex(1);
		CHECK(Arr.Compare(CopyArr));
		CopyArr.AddAtIndex('3', 0);

		Arr.Clear();
		CHECK(!Arr.Copy(CopyArr, 9, 0));
		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(EmptyArr));
		CHECK_EQUAL(0U, Arr.GetNumOfElements());

		CHECK(!Arr.Copy(CopyArr, 9, 1));
		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(EmptyArr));
		CHECK_EQUAL(0U, Arr.GetNumOfElements());

		CHECK(!Arr.Copy(CopyArr, 9, 99));
		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(EmptyArr));
		CHECK_EQUAL(0U, Arr.GetNumOfElements());

		// TODO: this fails? i can't copy an empty array?
		//CHECK(Arr.Copy(EmptyArr));
		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(EmptyArr));
		//CHECK_EQUAL(0U, Arr.GetNumOfElements());
	}

	TEST(Operator_Copy) {
		Arr.Clear();

		Array<char> CopyArr;
		CopyArr.Add('3');
		CopyArr.Add('2');
		CopyArr.Add('1');
		CopyArr.Add('0');

		Arr = CopyArr;
		CHECK(Arr.Compare(CopyArr));

		// TODO: we can't copy empty containers! look at TODO in TEST(Copy)
		CopyArr.Clear();
		Arr = CopyArr;
		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(CopyArr));
		//CHECK_EQUAL(0U, Arr.GetNumOfElements());
	}

	TEST(Compare) {
		Arr.Clear();

		Array<char> CompareArr, EmptyArr;
		CompareArr.Add('3');
		CompareArr.Add('2');
		CompareArr.Add('1');
		CompareArr.Add('0');

		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr.Compare(EmptyArr));

		Arr = CompareArr;

		CHECK(Arr.Compare(CompareArr));

		CHECK(Arr.Compare(CompareArr, 0, 0));
		CHECK(Arr.Compare(CompareArr, 0, 2));
		CHECK(Arr.Compare(CompareArr, 0, Arr.GetNumOfElements()));

		CHECK(Arr.Compare(CompareArr, 1, 0));
		CHECK(Arr.Compare(CompareArr, 1, 2));
		CHECK(Arr.Compare(CompareArr, 1, Arr.GetNumOfElements()-1));

		CHECK(!Arr.Compare(CompareArr, 10, 0));
		CHECK(!Arr.Compare(CompareArr, 10, 2));
		CHECK(!Arr.Compare(CompareArr, 10, Arr.GetNumOfElements()));
	}

	TEST(Operator_Equals) {
		Arr.Clear();

		Array<char> CompareArr, EmptyArr;
		CompareArr.Add('3');
		CompareArr.Add('2');
		CompareArr.Add('1');
		CompareArr.Add('0');

		// TODO: Compare return false if both containers are empty!
		//CHECK(Arr == EmptyArr);

		Arr = CompareArr;
		CHECK(Arr == CompareArr);

		Arr.RemoveAtIndex(1);
		CHECK(!(Arr == CompareArr));
	}

	TEST(Operator_NotEquals) {
		Arr.Clear();

		Array<char> CompareArr, EmptyArr;
		CompareArr.Add('3');
		CompareArr.Add('2');
		CompareArr.Add('1');
		CompareArr.Add('0');

		// TODO: Compare return false if both containers are empty!
		//CHECK(!(Arr != EmptyArr));

		Arr = CompareArr;
		CHECK(!(Arr != CompareArr));

		Arr.RemoveAtIndex(1);
		CHECK(Arr != CompareArr);
	}
}