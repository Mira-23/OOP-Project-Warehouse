#pragma once
#include "Product.h"

/// <summary>
/// interface that covers all of the storage units, implements add/addDirectly for easier traversal of the multiple levels of the warehouse, and also contains a clone function so that any class can be used as an interface
/// </summary>
class StorageUnit
{
public:
	virtual bool add(Product* p) = 0;
	virtual bool addDirectly(Product* p) = 0;
	virtual StorageUnit* clone() = 0;

	virtual ~StorageUnit() = 0;
private:
};

