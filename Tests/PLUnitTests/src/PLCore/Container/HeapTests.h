#ifndef __HEAPTESTS_H__
#define __HEAPTESTS_H__
#pragma once

#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Heap.h>

using namespace PLCore;

template <class KeyType, class ValType>
void CheckDerivedHeapFunctions(Heap<KeyType, ValType>& map) {
	// TODO: test functions!
	/*
	bool map.add(const KeyType &Key, const ValueType &Value);
	bool GetTop(ValueType *pValue=nullptr, KeyType *pKey=nullptr);
	bool ExtractTop(ValueType *pValue=nullptr, KeyType *pKey=nullptr);
	*/
	// isEmpty_and_Clear
	{
		map.Clear();
		CHECK(map.IsEmpty());
		CHECK_EQUAL(0U, map.GetNumOfElements());

		map.Add(1, 1);
		CHECK(!map.IsEmpty());
		CHECK_EQUAL(1U, map.GetNumOfElements());
	}

	// add
	{
		map.Clear();
		CHECK(map.Add(0, 0));
		CHECK(map.Add(1, 0));
		CHECK(map.Add(2, 2));
		CHECK(map.Add(2, 8));
		CHECK(map.Add(3, 3));
	}

	// GetTop
	{
		int key, val;
		CHECK(map.GetTop(&val, &key));
		CHECK_EQUAL(0, key);
		CHECK_EQUAL(0, val);
		CHECK_EQUAL(5U, map.GetNumOfElements());
	}

	// ExtractTop
	{
		int key, val;
		CHECK(map.ExtractTop(&val, &key));
		CHECK_EQUAL(0, key);
		CHECK_EQUAL(0, val);
		CHECK_EQUAL(4U, map.GetNumOfElements());

		// check next set
		CHECK(map.GetTop(&val, &key));
		CHECK_EQUAL(1, key);
		CHECK_EQUAL(0, val);
	}


	// TODO: test iterator!
}
#endif // __HEAPTESTS_H__