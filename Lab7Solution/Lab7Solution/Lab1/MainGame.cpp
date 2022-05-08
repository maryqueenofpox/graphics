#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transformMonkey;
Transform transformBanana;
Transform transformSword;
Transform transformSun;

using namespace glm;
using namespace std;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Shader fogShader();
	Shader rimShader();
	Shader geoShader();
	Shader reflectionShader();

	Shader customShader();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	
	monkeyMesh.loadModel("..\\res\\monkey3.obj");
	bananaMesh.loadModel("..\\res\\banana.obj");
	swordMesh.loadModel("..\\res\\sword.obj");

	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); 
	rimShader.init("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	reflectionShader.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");

	swordTexture.init("..\\res\\swordShader.png");
	bananaTexture.init("..\\res\\bananatexture.jpg");
	//basicShader.init("..\\res\\basicShader.vert", "..\\res\\basicShader.frag");

	customShader.init("..\\res\\customShader.vert", "..\\res\\customShader.frag");

	geoShader.initGeo();

	myCamera.initCamera(vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<string> hellfaces
	{
		"..\\res\\hellskybox\\right.png",
		"..\\res\\hellskybox\\left.png",
		"..\\res\\hellskybox\\top.png",
		"..\\res\\hellskybox\\bottom.png",
		"..\\res\\hellskybox\\front.png",
		"..\\res\\hellskybox\\back.png"
	};

	skybox.init(hellfaces);

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(monkeyMesh.getSpherePos(), monkeyMesh.getSphereRadius(), bananaMesh.getSpherePos(), bananaMesh.getSphereRadius());
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(vec3 m1Pos, float m1Rad, vec3 m2Pos, float m2Rad)
{
	float distance = sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::linkFogShader()
{
	fogShader.setFloat("maxDist", 20.0f);
	fogShader.setFloat("minDist", 0.0f);
	fogShader.setVec3("fogColor", vec3(0.0f, 0.0f, 0.0f));
}

void MainGame::linkReflection()
{
	reflectionShader.setMat4("model", transformMonkey.GetModel());
	reflectionShader.setMat4("view", myCamera.getView());
	reflectionShader.setMat4("projection", myCamera.getProjection());
	reflectionShader.setInt("skybox", 0);
	reflectionShader.setVec3("cameraPos", myCamera.getPos());
	reflectionShader.setFloat("time", cos(counter));
}

void MainGame::linkGeo()
{
	geoShader.setFloat("time", counter);
}

void MainGame::linkCustomShader()
{
	customShader.setMat4("projection", myCamera.getProjection());
	customShader.setMat4("view", myCamera.getView());
	customShader.setMat4("model", transformBanana.GetModel());
	customShader.setVec3("lightColour", vec3(1.0f, 1.0f, 1.0f));
	customShader.setVec3("lightPosition", myCamera.getPos());
	customShader.setVec3("viewPosition", myCamera.getPos());
}

void MainGame::linkRimLighting()
{
	vec3 camDir;
	camDir = bananaMesh.getSpherePos() - myCamera.getPos();
	camDir = glm::normalize(camDir);
	rimShader.setMat4("u_pm", myCamera.getProjection());
	rimShader.setMat4("u_vm", myCamera.getView());
	rimShader.setMat4("model", transformMonkey.GetModel());
	rimShader.setMat4("view", myCamera.getView());
	rimShader.setVec3("lightDir", vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets background colour
	
	transformMonkey.SetPos(vec3(sinf(counter), -1.1, 0));
	transformMonkey.SetRot(vec3(0.0, counter, 0));
	transformMonkey.SetScale(vec3(0.7, 0.7, 0.7));

	reflectionShader.Bind();
	linkReflection();
	reflectionShader.Update(transformMonkey, myCamera);

	monkeyMesh.draw();
	monkeyMesh.updateSphereData(*transformMonkey.GetPos(), 0.62f);

	transformBanana.SetPos(vec3(0.0, 0.0, 0.3 + sinf(counter)));
	transformBanana.SetRot(vec3(0.0, 0.0, 0.0));
	transformBanana.SetScale(vec3(0.01, 0.01, 0.01));


	customShader.Bind();
	linkCustomShader();
	customShader.Update(transformBanana, myCamera);

	bananaTexture.Bind(0);
	bananaMesh.draw();
	bananaMesh.updateSphereData(*transformBanana.GetPos(), 0.62f);

	transformSword.SetPos(vec3(2.0, 1.3 + sinf(counter), 0.0));
	transformSword.SetRot(vec3(-90.0, 0.0, counter * 2));
	transformSword.SetScale(vec3(0.05, 0.05, 0.05));

	geoShader.Bind();
	linkGeo();
	geoShader.Update(transformSword, myCamera);
	swordTexture.Bind(0);

	swordMesh.draw();
	swordMesh.updateSphereData(*transformSword.GetPos(), 0.62f);

	counter = counter + 0.01f;

	skybox.draw(&myCamera);	
	

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();


	_gameDisplay.swapBuffer();	
	

} 