#ifndef LevelEditor_H_
#define LevelEditor_H_

#include "MayaReader.h"
#include "gameplay.h"
#include "DataTypes.h"
#include <string>

using namespace gameplay;

/**
* Main game class.
*/
class LevelEditor : public Game
{
private:
#pragma region MAPSHIT
	//struct cmp_str : public std::binary_function<const char*, const char*, bool> 
	//{
	//	bool operator()(const char *a, const char *b)
	//	{
	//		return std::strcmp(a, b) < 0;
	//	}
	//};

	//struct mat_cmp
	//{
	//	bool operator()(const Material*a, const Material *b)
	//	{
	//		return(a == b);
	//	}
	//};

	MayaReader * mayaReader;
	std::unordered_map<std::string, Material*> materialMap;
	//typedef std::unordered_map<Material*, Texture*, mat_cmp> textureMap;
	//materialMap mMap;
	//textureMap tMap;
#pragma endregion

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
