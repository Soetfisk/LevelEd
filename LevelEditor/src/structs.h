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
		unsigned int normalIndexCount;
		/*The name will be placed after the vertices and poop
		, this number will be the exact number of characters
		that make up the name. So put a null byte at nameLength+1*/
		unsigned int uvCount;
		unsigned int uvIndexCount;
		unsigned int materialNameLength;
	};
	struct nameChanged
	{
		unsigned int nameLength;
		unsigned int newNameLength;
	};
	struct Transformation
	{
		unsigned int nrOfMeshes;
		unsigned int modified;
	};
	struct modVertInfo
	{
		unsigned int nameLength;
		unsigned int nrOfVertices;
		unsigned int indexLength;
	};
	struct vertexWID
	{
		unsigned int id;
		float x, y, z;
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
	struct U
	{
		float u;
	};
	struct V
	{
		float v;
	};
	struct vertexData
	{
		float x, y, z;
		float nx, ny, nz;
		//float r, g, b;
		float u, v;
	};
	struct doubleMatrix
	{
		double m[16];
	};

	struct floatMatrix
	{
		float m[16];
	};

	struct CreateMaterial
	{
		unsigned int texturePathLength;
		unsigned int normalPathLength;
		unsigned int ambientPathLength;
		unsigned int specularPathlength;
		unsigned int nameLength;
		bool specular;
	};
	struct ambient
	{
		float r, g, b;
	};
	struct diffuse
	{
		float r, g, b, coeff;
	};
	struct specular
	{
		float r, g, b, shine;
	};