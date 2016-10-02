#include "LevelEditor.h"

// Declare our game instance
LevelEditor game;

LevelEditor::LevelEditor()
	: _scene(NULL), _wireframe(false)
{
}

void LevelEditor::initialize()
{
	_scene = Scene::create();
	Node * lightNode = Node::create("pointLightShape1");
	Light * light = Light::createPoint(Vector3(0.5f, 0.5f, 0.5f), 25);

	lightNode->setLight(light);
	lightNode->translate(Vector3(0.f, 0.f, 0.f));

	_scene->addNode(lightNode);

	lightNode->release();
	light->release();

	//kiss->setVertexData(vertexData, vertexStart, vertexCount)
	//kuken->draw();



	// Set the aspect ratio for the scene's camera to match the current resolution
	_scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void LevelEditor::finalize()
{
	SAFE_RELEASE(_scene);
}

void LevelEditor::update(float elapsedTime)
{
	//READ MAYA DATA HERE
	//mayastuff.read()



	// Rotate model
	_scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
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

Mesh * LevelEditor::createMesh(const void* vertexData, unsigned int vertexCount)
{

	VertexFormat::Element elements[] =
	{
		VertexFormat::Element(VertexFormat::POSITION, 3),
		VertexFormat::Element(VertexFormat::COLOR, 3)
	};
	Mesh* mesh = Mesh::createMesh(VertexFormat(elements, 2), vertexCount, false);
	if (mesh == NULL)
	{
		GP_ERROR("Failed to create mesh.");
		return NULL;
	}
	mesh->setPrimitiveType(Mesh::TRIANGLE_STRIP);

	mesh->setVertexData(vertexData, 0, vertexCount);
	return mesh;

}
