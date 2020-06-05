#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED
#include <vector>
#include "Node.h"
#include "Market.h"
#include "StoreHouse.h"
#include "Way.h"
#include <math.h>

using namespace std;

class Route {
public:
	vector<Market> wh;
	vector<Way> Ways;
	StoreHouse store;

	void setStore(StoreHouse store) {
		this->store=store;
	}

	void setMarket(Market newMarket) {
		wh.push_back(newMarket);
	}

	void setWay(Way newWay) {
		Ways.push_back(newWay);
	}

	float shrtWay(Node bg, Node end) {
		return sqrt(pow((bg.i-end.i),2)+ pow((bg.j - end.j),2));
	}
};
#endif // ROUTE_H_INCLUDED
