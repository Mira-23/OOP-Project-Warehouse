#pragma once
#include "Product.h"

class IStorageUnit
{
public:
	virtual bool add(Product p) = 0;
	~IStorageUnit();
private:
};

