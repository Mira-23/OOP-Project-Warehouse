#pragma once
#include "Product.h"

class IStorageUnit
{
public:
	virtual bool add(Product* p) = 0;
	virtual bool isEmpty() = 0;
	virtual ~IStorageUnit() = 0;
private:
};

