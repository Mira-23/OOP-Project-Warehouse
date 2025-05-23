#pragma once
#include "Shelf.h"
#include <vector>
class Warehouse
{
public:
	Warehouse();
	void print() const;
	void add();
	void remove();
	void log() const;
	void clean();
private:
	std::vector<Shelf> shelves;
	const int shelfCapacity = 100;
};

