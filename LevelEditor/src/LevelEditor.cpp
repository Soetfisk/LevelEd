#include "LevelEditor.h"
#include <stdio.h>
#include "Windows.h"
#include "Wincon.h"

// Declare our game instance
LevelEditor game;

void InitDosConsole() {
	AllocConsole();
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
}


LevelEditor::LevelEditor()
	: _scene(NULL), _wireframe(false)
{
}

LevelEditor::~LevelEditor()
{
	delete mayaReader;
}

void LevelEditor::initialize()
{

	InitDosConsole();

	mayaReader = new MayaReader();

	_scene = Scene::create();
	_scene->setAmbientColor(1.0, 1.0, 1.0);

	Node * lightnode = Node::create("pointLightShape1");
	Light * light = Light::createPoint(Vector3(0.5f, 0.5f, 0.5f), 25);

	lightnode->setLight(light);
	lightnode->translate(Vector3(1.f, 1.f, 0.f));

	_scene->addNode(lightnode);

	lightnode->release();
	light->release();

#pragma region TESTS
	

	Camera * Camera = Camera::createPerspective(45.0,
		getAspectRatio(), 1.0f, 100.0f);

	Node * cameraNode = _scene->addNode("p");
	cameraNode->setCamera(Camera);
	_scene->setActiveCamera(Camera);

	SAFE_RELEASE(Camera);

	cameraNode->translate(0, 1, 5);
	cameraNode->rotateX(MATH_DEG_TO_RAD(-11.25f));


	
	// Create a white light.
	//Light* light = Light::createDirectional(0.75f, 0.75f, 0.75f);
	//Node* lightNode = _scene->addNode("light");
	//lightNode->setLight(light);
	////cam->setProjectionMatrix(projectionMatrix);
	//SAFE_RELEASE(light);
	//printf("dir light: %f, %f, %f \n", lightNode->getForwardVectorView().x, lightNode->getForwardVectorView().y, lightNode->getForwardVectorView().z);

	//lightNode->rotateX(MATH_DEG_TO_RAD(-45.0f));

	//printf("camera translation: %f, %f, %f \n", cameraNode->getTranslation().x, cameraNode->getTranslation().y, cameraNode->getTranslation().z);

	//printf("dir light: %f, %f, %f \n", lightNode->getForwardVectorView().x, lightNode->getForwardVectorView().y, lightNode->getForwardVectorView().z);

	//createTestMesh();
#pragma endregion



	// Set the aspect ratio for the scene's camera to match the current resolution
	//_scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void LevelEditor::finalize()
{
	SAFE_RELEASE(_scene);
}

void LevelEditor::update(float elapsedTime)
{
	char* Node = nullptr;
	unsigned int Case;

	Case = mayaReader->handleData(Node); //READ AND HANDLE FIRST HEADER

		 //READ SECOND HEADER FOR SPECIFIC TYPES

	switch (Case)
	{
		case MayaReader::MESH_NEW:
		{
			createTestMesh(Node);
			break;
		}

		case MayaReader::MATERIAL_NEW:
		{
			break;
		}

		case MayaReader::TRANSFORM:
		{
			modifyTransform(Node);
			break;
		}
		case MayaReader::CAMERA_NEW:
		{
			createCamera(Node);
			break;
		}


		case MayaReader::TEXTURE_NEW:

		case MayaReader::NUMBER_OF_SETTINGS:
			break;
		case MayaReader::MATERAL_CHANGED:
		case MayaReader::VERTEX_CHANGE:
		case MayaReader::CAMERA_CHANGED:
		case MayaReader::DELETED:

		default:
			break;
	}

	
	}
	




	// Rotate model
	//_scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));


void LevelEditor::render(float elapsedTime)
{
	// Clear the color and depth buffers
	clear(CLEAR_COLOR_DEPTH, Vector4(1.0, 1.0 ,1.0 ,1.0), 1.0f, 0);




	// Visit all the nodes in the scene for drawing
	_scene->visit(this, &LevelEditor::drawScene);
}

bool LevelEditor::drawScene(Node* node)
{
	// If the node visited contains a drawable object, draw it
	Drawable* drawable = node->getDrawable();
	if (drawable)
		drawable->draw(_wireframe);

	return true;
}

void LevelEditor::keyEvent(Keyboard::KeyEvent evt, int key)
{
	if (evt == Keyboard::KEY_PRESS)
	{
		switch (key)
		{
		case Keyboard::KEY_ESCAPE:
			exit();
			break;
		}
	}
}

void LevelEditor::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
	switch (evt)
	{
	case Touch::TOUCH_PRESS:
		_wireframe = !_wireframe;
		break;
	case Touch::TOUCH_RELEASE:
		break;
	case Touch::TOUCH_MOVE:
		break;
	};
}

//void LevelEditor::createMesh(const void* meshData)
//{
//
//	Node * node = _scene->findNode(((DataType::Mesh*)meshData)->name);
//	Material * material = nullptr;
//
//
//	if (node)
//	{
//		//ta bort vertisdata
//		//läs in material
//	}
//	else
//	{
//		node = Node::create(((DataType::Mesh*)meshData)->name);
//	}
//
//	VertexFormat::Element elements[] =
//	{
//		VertexFormat::Element(VertexFormat::POSITION, 3),
//		VertexFormat::Element(VertexFormat::COLOR, 3)
//	};
//
//	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), ((DataType::Mesh*)meshData)->vertexCount, false);
//	
//	if (mesh == NULL)
//	{
//		GP_ERROR("Failed to create mesh.");
//		return;
//	}
//
//	mesh->setPrimitiveType(Mesh::TRIANGLE_STRIP);
//	mesh->setVertexData((char*)meshData + sizeof(DataType::Mesh),
//		0, 
//		((DataType::Mesh*)meshData)->vertexCount);
//	
//	MeshPart * meshPart = mesh->addPart(
//		Mesh::PrimitiveType::TRIANGLE_STRIP,
//		Mesh::IndexFormat::INDEX32,
//		((DataType::Mesh*)meshData)->topologyCount,
//		true
//	);
//
//	//pointer to topologydata ->  (char*)meshData +sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount)
//
//	meshPart->setIndexData((char*)meshData + sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount),
//		0, 
//		((DataType::Mesh*)meshData)->topologyCount
//	);
//
//	Model * model = Model::create(mesh);
//	
//	if (material)
//		model->setMaterial(material);
//
//	node->setDrawable(model);
//
//	_scene->addNode(node);
//
//	//LÄGG TILL: om meshen fanns innan -> ta bort den
//}

void LevelEditor::createTestMesh(char* msg)
{
 
	char * name = (msg + sizeof(CreateMesh));
	name[*(unsigned int*)msg + 1] = '\0';

	//Node * node = _scene->findNode((msg + sizeof(unsigned int)));
	Node * node = _scene->findNode(name);
	if (node)
	{
		//ta bort vertisdata
		//läs in material
	}
	else
	{
		node = Node::create(name);
	}

	//msg += (*(unsigned int*)msg + sizeof(unsigned int));
	//msg += (*(unsigned int*)msg + sizeof(CreateMesh));

	CreateMesh* mMesh;
	Vertex *mVertex;
	Index *mIndex, *mNormalIndex;
	Normals *mNormal;


	mMesh = (CreateMesh*)(msg);
	msg += mMesh->nameLength + sizeof(CreateMesh);
	
	node->set(((float*)msg), Quaternion(&((float*)msg)[3]), (&((float*)msg)[7])); //set translation values
	msg += sizeof(float) * 10;

	printf("%d, %d, %d ", mMesh->indexCount, mMesh->normalCount, mMesh->vertexCount);
	mVertex = new Vertex[mMesh->vertexCount];
	mIndex = new Index[mMesh->indexCount];

	//msg += sizeof(CreateMesh);
	mVertex = (Vertex*)(msg);

	msg += sizeof(Vertex)*mMesh->vertexCount;
	mIndex = (Index*)(msg);

	msg += sizeof(Index)*mMesh->indexCount;
	mNormal = (Normals*)(msg);

	msg += sizeof(Normals)*mMesh->normalCount;
	mNormalIndex = (Index*)(msg);

	msg += sizeof(Index)*mMesh->indexCount;

	unsigned int indexList[36];
	vertexData * vData = new vertexData[mMesh->indexCount];
	for (size_t i = 0; i < mMesh->indexCount; i++)
	{
		vData[i].x = mVertex[mIndex[i].nr].x;
		vData[i].y = mVertex[mIndex[i].nr].y;
		vData[i].z = mVertex[mIndex[i].nr].z;
		vData[i].nx = mNormal[mNormalIndex[i].nr].x;
		vData[i].ny	= mNormal[mNormalIndex[i].nr].y;
		vData[i].nz	= mNormal[mNormalIndex[i].nr].z;

		vData[i].r = 150.f;
		vData[i].g = 150.f;
		vData[i].b = 150.f;

		indexList[i] = i;
	}
	/*for (size_t i = 0; i < mMesh->vertexCount; i++)
	{
		int t = i * 4;
		vData[i].x = mVertex[i].x;
		vData[i].y = mVertex[i].y;
		vData[i].z = mVertex[i].z;
		vData[i].nx = mNormal[t].x;
		vData[i].ny = mNormal[t].y;
		vData[i].nz = mNormal[t].z;
	}*/

	//for (size_t i = 0; i < mMesh->vertexCount; i++)
	//{
	//	printf("VERTEX POS %d: %f, %f, %f\n", (i+1), mVertex[i].x, mVertex[i].y, mVertex[i].z);
	//}

	//printf("\n\n");

	//for (size_t i = 0; i < mMesh->indexCount; i++)
	//{
	//	printf("VERTEX INDEX %d: %d\n", (i + 1), mIndex[i].nr);
	//}

	//printf("\n\n");

	//for (size_t i = 0; i < mMesh->normalCount; i++)
	//{
	//	printf("NORMAL %d: %f, %f, %f\n", (i + 1), mNormal[i].x, mNormal[i].y, mNormal[i].z);
	//}

	//printf("\n\n");

	//for (size_t i = 0; i < mMesh->indexCount; i++)
	//{
	//	printf("NORMAL INDEX %d: %d\n", (i + 1), mNormalIndex[i].nr);
	//}



#pragma region creatingggggg


	
	//Material * material = Material::create("res/demo.material");
	Material * material = Material::create("res/shaders/colored.vert", "res/shaders/colored.frag", "POINT_LIGHT_COUNT 1");

	RenderState::StateBlock* block = RenderState::StateBlock::create();
	block->setCullFace(true);
	block->setDepthTest(true);
	material->setStateBlock(block);
	material->setParameterAutoBinding("u_worldViewMatrix", RenderState::AutoBinding::WORLD_VIEW_MATRIX);
	material->setParameterAutoBinding("u_worldViewProjectionMatrix", RenderState::AutoBinding::WORLD_VIEW_PROJECTION_MATRIX);
	material->setParameterAutoBinding("u_inverseTransposeWorldViewMatrix", RenderState::AutoBinding::INVERSE_TRANSPOSE_WORLD_VIEW_MATRIX);

	Node* lightNode = _scene->findNode("pointLightShape1");
	material->getParameter("u_pointLightColor[0]")->bindValue(lightNode->getLight(), &Light::getColor);
	material->getParameter("u_pointLightRangeInverse[0]")->bindValue(lightNode->getLight(), &Light::getRangeInverse);
	material->getParameter("u_pointLightPosition[0]")->bindValue(lightNode, &Node::getTranslationView);
	


	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::NORMAL, 3),
		VertexFormat::Element(VertexFormat::COLOR, 3)
	};

	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 3), mMesh->indexCount, true);

	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return;
	}

	mesh->setPrimitiveType(Mesh::TRIANGLES);
	mesh->setVertexData(vData),
		0,
		(mMesh->indexCount);

	MeshPart * meshPart = mesh->addPart(
		Mesh::PrimitiveType::TRIANGLES,
		Mesh::IndexFormat::INDEX32,
		mMesh->indexCount,
		true
	);

	//pointer to topologydata ->  (char*)meshData +sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount)

	meshPart->setIndexData(&indexList,
		0,
		mMesh->indexCount
	);

	Model * model = Model::create(mesh);

	

	if (material)
		model->setMaterial(material);

	node->setDrawable(model);
	node->translateZ(3.0f);

	printf(("Mesh Translate: %f, %f, %f \n"), node->getTranslation().x, node->getTranslation().y, node->getTranslation().z);

	_scene->addNode(node);

#pragma endregion
}

void LevelEditor::createCamera(char * msg)
{
	char * name = (msg + sizeof(unsigned int));
	name[*(unsigned int*)msg + 1] = '\0';
	Node * node;
	//node = _scene->findNode(msg + sizeof(unsigned int));
	node = _scene->findNode("p"); //just checking the first place in the char pointer

	Camera * camera;

	if (!node)
	{
		node = _scene->addNode(msg + sizeof(unsigned int));
		camera = Camera::createPerspective(45.0,
			getAspectRatio(), 1.0f, 100.0f);
		node->setCamera(camera);
	}
	else
	{
		camera = node->getCamera();
	}
	msg += *(unsigned int*)msg + sizeof(unsigned int);

	camera->setProjectionMatrix(*(Matrix*)msg);
	msg += sizeof(Matrix);

	node->set({ 1.0, 1.0, 1.0 }, Quaternion(((float*)msg)), (&((float*)msg)[4])); //set translation values
	_scene->setActiveCamera(camera);

	SAFE_RELEASE(camera);

}

void LevelEditor::modifyTransform(char * msg)
{

	char * name = (msg + sizeof(Transformation));
	unsigned int * kuk = (unsigned int*)msg;
	name[*(unsigned int*)msg] = '\0';
	Node * node;
	node = _scene->findNode(name); //just checking the first place in the char pointer
	//msg += sizeof(unsigned int);

	msg += sizeof(unsigned int);
	unsigned int Case = (*(unsigned int*)msg);

	msg += *kuk + sizeof(unsigned int);


	switch (Case)
	{
	case MayaReader::SCALE:
		break;
	case MayaReader::ROTATION:
		break;
	case MayaReader::TRANSLATION:
		break;
	case MayaReader::ALL:
	{
		node->set(((float*)msg), Quaternion(&((float*)msg)[3]), (&((float*)msg)[7])); //set translation values
		break;
	}

	default:
		break; //självmord
	}

	//float * translate;
	//float * scale;
	//float * rotationQuat;

	//translate = ((float*)(msg));
	//msg += sizeof(float) * 3;

	//scale = ((float*)(msg));
	//msg += sizeof(float) * 3;

	//rotationQuat = ((float*)(msg));
	//msg += sizeof(float) * 4;



}
