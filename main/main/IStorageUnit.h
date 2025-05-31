#pragma once
#include "Product.h"

class IStorageUnit
{
public:
	virtual bool add(Product* p) = 0;
	virtual bool addDirectly(Product* p) = 0;

	virtual ~IStorageUnit() = 0;
private:
};

