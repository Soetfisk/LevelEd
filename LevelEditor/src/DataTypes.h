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
	float x, y, z; //pos
	float r, g, b; //temp
	float nx, ny, nz; //normal
};

struct Topology
{
	unsigned int nr;
};


}