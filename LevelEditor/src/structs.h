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
		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int normalCount;
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