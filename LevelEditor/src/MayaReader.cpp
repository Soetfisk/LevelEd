#include "MayaReader.h"



MayaReader::MayaReader() 
{
	circularBuffer = new CircularBuffer(L"poop3", 200, false, 256);
}
MayaReader::~MayaReader() 
{
	delete circularBuffer;
	delete msg;
}

MayaReader::MsgContain MayaReader::handleData(char *& Node) //reference to pointer in order to change the adress
{
	msg = new char[(200 * 1 << 10) / 4];

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
