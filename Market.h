#ifndef MARKET_H_INCLUDED
#define MARKET_H_INCLUDED
#include "Node.h"

class Market : public Node {
public:

	Market(int i, int j) {
		this->i = i;
		this->j = j;
	}
};
#endif // MARKET_H_INCLUDED
