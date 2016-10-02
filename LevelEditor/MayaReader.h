#pragma once
class MayaReader
{
public:
	MayaReader();
	~MayaReader();

private:


	enum
	{
		NEW_MESH,
		VERTEX_CHANGE,
		NEW_MATERIAL,
		MATERAL_CHANGED,
		TRANSFORM,
		CAMERA,
		CAMERA_CHANGED,
		TEXTURE,
		DELETED,

		NUMBER_OF_SETTINGS
	};


};

MayaReader::MayaReader()
{
}

MayaReader::~MayaReader()
{
}