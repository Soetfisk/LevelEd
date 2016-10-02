#include "LevelEditor.h"


// Declare our game instance
LevelEditor game;

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
	mayaReader = new MayaReader();

	_scene = Scene::create();
	Node * lightNode = Node::create("pointLightShape1");
	Light * light = Light::createPoint(Vector3(0.5f, 0.5f, 0.5f), 25);

	lightNode->setLight(light);
	lightNode->translate(Vector3(1.f, 0.f, 0.f));

	_scene->addNode(lightNode);

	lightNode->release();
	light->release();

#pragma region TESTS
	createTestMesh();


	//float camMatrix[4][4];
	Node * cameraNode = Node::create("kuk_camera");
	_scene->addNode(cameraNode);
	Camera* cam = cameraNode->getCamera();
	cam = Camera::createPerspective(60, 1920/1080, 0, 1000);
	cameraNode->setCamera(cam);


	//cam->setProjectionMatrix(projectionMatrix);

	_scene->setActiveCamera(cameraNode->getCamera());
#pragma endregion

	

	//kiss->setVertexData(vertexData, vertexStart, vertexCount)
	//kuken->draw();



	// Set the aspect ratio for the scene's camera to match the current resolution
	//_scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void LevelEditor::finalize()
{
	SAFE_RELEASE(_scene);
}

void LevelEditor::update(float elapsedTime)
{
	void* Node = nullptr;
	unsigned int Case;



	Case = mayaReader->read(); //READ AND HANDLE FIRST HEADER
	switch (Case)
	{
	case MayaReader::CREATE:
		
		Case = mayaReader->handleData(Node); //READ SECOND HEADER FOR SPECIFIC TYPES
		switch (Case) 
		{
		case MayaReader::NEW_MESH:
			createMesh(Node);

		case MayaReader::NEW_MATERIAL:
		case MayaReader::TRANSFORM:
		case MayaReader::CAMERA:
		case MayaReader::TEXTURE:


		default:
			break;
		}


	case MayaReader::CHANGE:

		Case = mayaReader->handleData(Node); //READ SECOND HEADER FOR SPECIFIC TYPES
		switch (Case) 
		{
		case MayaReader::MATERAL_CHANGED:
		case MayaReader::VERTEX_CHANGE:
		case MayaReader::CAMERA_CHANGED:
		case MayaReader::DELETED:

		default:
			break;
		}

	default:
		break;
	}





	// Rotate model
	//_scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void LevelEditor::render(float elapsedTime)
{
	// Clear the color and depth buffers
	clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);




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

void LevelEditor::createMesh(const void* meshData)
{

	Node * node = _scene->findNode(((DataType::Mesh*)meshData)->name);
	Material * material = nullptr;


	if (node)
	{
		//ta bort vertisdata
		//läs in material
	}
	else
	{
		node = Node::create(((DataType::Mesh*)meshData)->name);
	}

	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::COLOR, 3)
	};

	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), ((DataType::Mesh*)meshData)->vertexCount, false);
	
	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return;
	}

	mesh->setPrimitiveType(Mesh::TRIANGLE_STRIP);
	mesh->setVertexData((char*)meshData + sizeof(DataType::Mesh),
		0, 
		((DataType::Mesh*)meshData)->vertexCount);
	
	MeshPart * meshPart = mesh->addPart(
		Mesh::PrimitiveType::TRIANGLE_STRIP,
		Mesh::IndexFormat::INDEX32,
		((DataType::Mesh*)meshData)->topologyCount,
		true
	);

	//pointer to topologydata ->  (char*)meshData +sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount)

	meshPart->setIndexData((char*)meshData + sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount),
		0, 
		((DataType::Mesh*)meshData)->topologyCount
	);

	Model * model = Model::create(mesh);
	
	if (material)
		model->setMaterial(material);

	node->setDrawable(model);

	_scene->addNode(node);

	//LÄGG TILL: om meshen fanns innan -> ta bort den
}

void LevelEditor::createTestMesh()
{
	Node * node = _scene->findNode(mayaReader->testMesh->name);
	Material * material = nullptr;


	if (node)
	{
		//ta bort vertisdata
		//läs in material
	}
	else
	{
		node = Node::create(mayaReader->testMesh->name);
	}

	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::COLOR, 3)
	};

	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), mayaReader->testMesh->vertexCount, false);

	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return;
	}

	mesh->setPrimitiveType(Mesh::TRIANGLES);
	mesh->setVertexData(mayaReader->testVertexData),
		0,
		(mayaReader->testMesh->vertexCount);

	MeshPart * meshPart = mesh->addPart(
		Mesh::PrimitiveType::TRIANGLES,
		Mesh::IndexFormat::INDEX32,
		mayaReader->testMesh->topologyCount,
		true
	);

	//pointer to topologydata ->  (char*)meshData +sizeof(DataType::Mesh) + (sizeof(DataType::Vertex) * ((DataType::Mesh*)meshData)->vertexCount)

	meshPart->setIndexData(mayaReader->testTopology,
		0,
		mayaReader->testMesh->topologyCount
	);

	Model * model = Model::create(mesh);

	if (material)
		model->setMaterial(material);

	node->setDrawable(model);

	_scene->addNode(node);
}
