#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "SkyBox.h"

enum class GameState{PLAY, EXIT};

using namespace glm;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawScene();
	void linkFogShader();
	void linkRimLighting();
	void linkGeo();
	void linkCustomShader();
	void linkReflection();
	bool collision(vec3 m1Pos, float m1Rad, vec3 m2Pos, float m2Rad);

	Display _gameDisplay;
	GameState _gameState;
	Mesh monkeyMesh;
	Texture bananaTexture;
	Mesh bananaMesh;
	Texture swordTexture;
	Mesh swordMesh;
	Camera myCamera;

	Shader basicShader;
	Shader shaderSkybox;
	Shader fogShader;
	Shader rimShader;

	Shader customShader;
	Shader geoShader;
	Shader reflectionShader;

	Skybox skybox;


	float counter;
};

