#ifndef __MAPTESTS_H__
#define __MAPTESTS_H__
#pragma once

#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Map.h>

using namespace PLCore;

template <class KeyType, class ValueType>
void CheckDerivedMapFunctions(Map<KeyType, ValueType>& map) {
	/* TODO: test functions!
	void Clear()
	bool IsEmpty
	uint GetNumOfElements

	bool Add(key, value)
	ValueType Get(Key)

	bool Replace(key, newvalue)

	bool Set(key, value) // replace if key exists

	bool Remove(key)

	uint RemoveValue(value)
	*/


	// Clear(), IsEmpty(), GetNumOfElements()
	{
		map.Clear();
		CHECK(map.IsEmpty());
		CHECK_EQUAL(0U, map.GetNumOfElements());

		map.Add(0, 0);
		map.Add(1, 0);
		CHECK(!map.IsEmpty());
		CHECK_EQUAL(2U, map.GetNumOfElements());
	}

	// Add(key, value) and Get(key)
	{
		map.Clear();
		CHECK(map.Add(2, 2));
		CHECK(map.Add(5, 5));
		CHECK(map.Add(1, 1));
		
		CHECK_EQUAL(2, map.Get(2));
		CHECK_EQUAL(5, map.Get(5));
		CHECK_EQUAL(1, map.Get(1));
		CHECK_EQUAL(NULL, map.Get(99));
	}

	// Replace(key, newValue)
	{	
		CHECK_EQUAL(5, map.Get(5));
		CHECK(map.Replace(5, 6));
		CHECK_EQUAL(6, map.Get(5));

		CHECK(!map.Replace(99, 6));
	}

	// Set(key, Value)
	{	
		// adds element
		CHECK(!map.Set(10, 10));

		CHECK_EQUAL(6, map.Get(5));
		CHECK(map.Set(5, 5));
		CHECK_EQUAL(5, map.Get(5));
	}

	// Remove(key)
	{	
		CHECK(map.Remove(10));

		CHECK(!map.Remove(10));
	}

	// RemoveValue(value)
	{	
		CHECK(map.RemoveValue(5));

		CHECK(!map.RemoveValue(10));
	}
}
#endif // __MAPTESTS_H__