#include "Cell.h"



Cell::Cell()
{
}


Cell::~Cell()
{
}

void Cell::Insert(LPGAMEOBJECT object)
{
	listObj.push_back(object);
}
