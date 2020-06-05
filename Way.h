#ifndef WAY_H_INCLUDED
#define WAY_H_INCLUDED
#include "Node.h"

class Way {
public:
	Node bg, end;

	Way() {}
	Way(Node bg, Node end)
	{
		this->bg = bg;
		this->end = end;
	}
	void setbg(Node bg)
	{
		this->bg = bg;
	}
	void setEnd(Node end)
	{
		this->end = end;
	}
};
#endif // WAY_H_INCLUDED
