#pragma once

namespace DataType 
{

struct Mesh
{
	char name[256];
	unsigned int vertexCount;
	unsigned int topologyCount;
};

struct Vertex
{
	float x, y, z;
	float r, g, b; //temp
};

struct Topology
{
	unsigned int nr;
};


}