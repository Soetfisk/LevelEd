#pragma once

#include "structs.h"


class VertexData
{
public:
	VertexData();
	~VertexData();

	void pushData(char * data);



private:

	char * data;

};

