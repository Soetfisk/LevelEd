#include "MayaReader.h"



MayaReader::MayaReader() 
{
	circularBuffer = new CircularBuffer(L"poop3", 200, false, 256);
	msg = new char[(200 * 1 << 10)/4];
	rumpa = msg;
}
MayaReader::~MayaReader() 
{

	delete rumpa;
	delete circularBuffer;
}

MayaReader::MsgContain MayaReader::handleData(char *& Node) //reference to pointer in order to change the adress
{

	if (circularBuffer->pop(msg, length))
	{
		MsgContain type = (MsgContain)((TypeHeader*)msg)->type;

		msg += sizeof(TypeHeader);

		Node = msg;

		return type; //temp
	}
	else return NUMBER_OF_SETTINGS;
}

void MayaReader::cleanUp()
{
	
}
