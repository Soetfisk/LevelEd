#include "MayaReader.h"



MayaReader::MayaReader() 
{
	circularBuffer = new CircularBuffer(L"poop3", 10, true, 256);


//#pragma region initTestCube
//
//	float TESTCUBE[8*3] = {
//		-0.5, -0.5, 0.5,
//
//
//		0.5, -0.5, 0.5,
//
//
//		-0.5, 0.5, 0.5,
//
//
//		0.5, 0.5, 0.5,
//
//
//		-0.5, 0.5, -0.5,
//
//
//		0.5, 0.5, -0.5,
//
//
//		-0.5, -0.5, -0.5,
//
//
//		0.5, -0.5, -0.5,
//
//	};
//
//	float TestCubeNormals[24 * 3] =
//	{
//		0, 0, 1	,
//		0, 0, 1	,
//		0, 0, 1	,
//		0, 0, 1	,
//		0, 1, 0	,
//		0, 1, 0	,
//		0, 1, 0	,
//		0, 1, 0	,
//		0, 0, -1,
//		0, 0, -1,
//		0, 0, -1,
//		0, 0, -1,
//		0, -1, 0,
//		0, -1, 0,
//		0, -1, 0,
//		0, -1, 0,
//		1, 0, 0,
//		1, 0, 0,
//		1, 0, 0,
//		1, 0, 0,
//		-1, 0, 0,
//		-1, 0, 0,
//		-1, 0, 0,
//		-1, 0, 0
//	};
//
//	unsigned int BAJS[36] = { 0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 7, 1, 1, 7, 3, 3, 7, 5, 6, 0, 4, 4, 0, 2 };
//	unsigned int KISS[36] = { 0, 1, 3, 3, 1, 2, 4, 5, 7, 7, 5, 6, 8, 9, 11, 11, 9, 10, 12, 13, 15, 15, 13, 14, 16, 17, 19, 19, 17, 18, 20, 21, 23, 23, 21, 22 };  //
//
//	testMesh = new DataType::Mesh;
//	*testMesh = { "TestCube", (unsigned int)8, (unsigned int)36 };
//
//	testVertexData = new DataType::Vertex[36];
//	testTopology = new DataType::Topology[36];
//
//	testVertexData = (DataType::Vertex*)TESTCUBE;
//
//	for (size_t i = 0; i < 36; i+=3)
//	{
//
//		testVertexData[i].x = TESTCUBE[BAJS[i]];
//		testVertexData[i].y = TESTCUBE[BAJS[i + 1]];
//		testVertexData[i].z = TESTCUBE[BAJS[i + 2]];
//
//		testVertexData[i].r = 0.5;
//		testVertexData[i].g = 0.5;
//		testVertexData[i].b = 0.5;
//
//		testVertexData[i].nx = TestCubeNormals[KISS[i]];
//		testVertexData[i].ny = TestCubeNormals[KISS[i + 1]];
//		testVertexData[i].nz = TestCubeNormals[KISS[i + 2]];
//	}
//
//
//	testTopology = (DataType::Topology*)BAJS;
//
//
//	//for (size_t i = 0; i < 36; i++)
//	//{
//	//	char s[256];
//	//	sprintf(s, "%d,", testTopology[i]);
//	//	OutputDebugStringA(s);
//	//}
//#pragma endregion

	

}
MayaReader::~MayaReader() 
{
	delete circularBuffer;

}

MayaReader::MsgContain MayaReader::handleData(void *& Node) //reference to pointer in order to change the adress
{
	
	return NUMBER_OF_SETTINGS; //temp
}

MayaReader::MsgType MayaReader::read()
{
	msg = new char[(10 * 1 << 10) / 4];
	
	if (circularBuffer->pop(msg, length))
	{

		unsigned int test = ((MainHeader*)msg)->type;

		printf("%d", test);

		delete msg;
	}
	else
		return NUMBER_OF_TYPES; //temp
}