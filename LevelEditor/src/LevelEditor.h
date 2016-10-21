#ifndef LevelEditor_H_
#define LevelEditor_H_

#include "MayaReader.h"
#include "gameplay.h"
#include "DataTypes.h"

using namespace gameplay;

/**
* Main game class.
*/
class LevelEditor : public Game
{
private:
	MayaReader * mayaReader;
	
	Camera * perspCam;
	/**
	* Draws the scene each frame.
	*/
	bool drawScene(Node* node);

	Scene* _scene;
	bool _wireframe;
public:

	/**
	* Constructor.
	*/
	LevelEditor();

	/**
	* Destructor.
	*/
	~LevelEditor();

	/**
	* @see Game::keyEvent
	*/
	void keyEvent(Keyboard::KeyEvent evt, int key);

	/**
	* @see Game::touchEvent
	*/
	void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:


	//void createMesh(const void* vertexData);

	void modifyTransform(char * msg);
	void createTestMesh(char * msg);
	void createCamera(char * msg);
    void createMaterial(char* msg);
    void createTexture(char * msg);
	void modifyVertex(char * msg);
	void deleteElement(char * msg);
	void nameChange(char * msg);
	void changeCamera(char * msg);

	/**
	* @see Game::initialize
	*/
	void initialize();

	/**
	* @see Game::finalize
	*/
	void finalize();

	/**
	* @see Game::update
	*/
	void update(float elapsedTime);

	/**
	* @see Game::render
	*/
	void render(float elapsedTime);

};

#endif
