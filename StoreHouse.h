#ifndef STOREHOUSE_H_INCLUDED
#define STOREHOUSE_H_INCLUDED
#include "Node.h"

class StoreHouse : public Node{
public:

	StoreHouse() {}
	StoreHouse(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
};
#endif // STOREHOUSE_H_INCLUDED
