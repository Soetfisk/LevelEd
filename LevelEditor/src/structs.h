#pragma once

	struct MainHeader
	{
		unsigned int type;
	};
	struct TypeHeader
	{
		unsigned int type;
	};
	struct CreateMesh
	{
		unsigned int nameLength;
		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int normalCount;
		/*The name will be placed after the vertices and poop
		, this number will be the exact number of characters
		that make up the name. So put a null byte at nameLength+1*/
		unsigned int uvCount;
		unsigned int uvIndexCount;
	};
	struct Vertex
	{
		float x, y, z;
	};
	struct Index
	{
		int nr;
	};
	struct Normals
	{
		float x, y, z;
	};
	struct vertexData
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
		//float u, v;
	};
	struct doubleMatrix
	{
		double m[16];
	};

	struct floatMatrix
	{
		float m[16];
	};