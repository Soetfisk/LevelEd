#include "MayaReader.h"

MayaReader::MayaReader() 
{

#pragma region initTestCube
	testMesh = new DataType::Mesh;
	*testMesh = { "TestCube", (unsigned int)36, (unsigned int)36 };

	testVertexData = new DataType::Vertex[36];
	testTopology = new DataType::Topology[36];

	testVertexData = (DataType::Vertex*)TESTCUBE;

	for (unsigned int i = 0; i < 36; i++)
		testTopology[i].nr = i;
#pragma endregion

	

}
MayaReader::~MayaReader() 
{

}

unsigned int MayaReader::handleData(void *& Node) //reference to pointer in order to change the adress
{
	
	return 9999; //temp
}

unsigned int MayaReader::read()
{


	return 9999; //temp
}