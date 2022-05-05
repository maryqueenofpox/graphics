#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transformMonkey;
Transform transformBanana;
Transform transformSword;
Transform transformSun;

using namespace glm;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Shader fogShader();
	Shader toonShader();
	Shader rimShader();
	Shader geoShader();
	Shader reflectionShader();

	Shader customShader();
	//Audio* audioDevice();
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
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	monkeyMesh.loadModel("..\\res\\monkey3.obj");
	bananaMesh.loadModel("..\\res\\banana.obj");
	swordMesh.loadModel("..\\res\\sword.obj");
	sunMesh.loadModel("..\\res\\sun.obj");

	fogShader.init("..\\res\\fogShader.vert", "..\\res\\fogShader.frag"); //new shader
	toonShader.init("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag"); //new shader
	rimShader.init("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	reflectionShader.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");

	swordTexture.init("..\\res\\swordTexture.png");
	basicShader.init("..\\res\\basicShader.vert", "..\\res\\basicShader.frag");

	customShader.init("..\\res\\customShader.vert", "..\\res\\customShader.frag");

	geoShader.initGeo();

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	skybox.init(faces);

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(monkeyMesh.getSpherePos(), monkeyMesh.getSphereRadius(), bananaMesh.getSpherePos(), bananaMesh.getSphereRadius());
		//playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
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


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		//audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

//void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
//{
//	
//	ALint state; 
//	alGetSourcei(Source, AL_SOURCE_STATE, &state);
//	/*
//	Possible values of state
//	AL_INITIAL
//	AL_STOPPED
//	AL_PLAYING
//	AL_PAUSED
//	*/
//	if (AL_PLAYING != state)
//	{
//		audioDevice.playSound(Source, pos);
//	}
//}

void MainGame::linkFogShader()
{
	//fogShader.setMat4("u_pm", myCamera.getProjection());
	//fogShader.setMat4("u_vm", myCamera.getProjection());
	fogShader.setFloat("maxDist", 20.0f);
	fogShader.setFloat("minDist", 0.0f);
	fogShader.setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));
}

void MainGame::linkReflection()
{
	reflectionShader.setMat4("model", transformMonkey.GetModel());
	reflectionShader.setMat4("view", myCamera.getView());
	reflectionShader.setMat4("projection", myCamera.getProjection());
	reflectionShader.setInt("skybox", 0);
	reflectionShader.setVec3("cameraPos", myCamera.getPos());
}


void MainGame::linkToon()
{
	toonShader.setVec3("lightDir", transformMonkey.getPos());

}

void MainGame::linkGeo()
{


	float randX = ((float)rand() / (RAND_MAX));
	float randY = ((float)rand() / (RAND_MAX));
	float randZ = ((float)rand() / (RAND_MAX));
	// Frag: uniform float randColourX; uniform float randColourY; uniform float randColourZ;
	geoShader.setFloat("randColourX", randX);
	geoShader.setFloat("randColourY", randY);
	geoShader.setFloat("randColourZ", randZ);
	// Geom: uniform float time;

	//geoShader.setInt("image", swordTexture.Bind(0));
	geoShader.setFloat("time", counter);


}

void MainGame::linkCustomShader()
{
	customShader.setMat4("projection", myCamera.getProjection());
	customShader.setMat4("view", myCamera.getView());
	customShader.setMat4("model", transformBanana.GetModel());
	customShader.setVec3("lightColour", glm::vec3(1.0f, 1.0f, 1.0f));
	customShader.setVec3("objectColour", glm::vec3(0.55f, 0.95f, 0.89f));
	customShader.setVec3("lightPosition", transformMonkey.getPos());
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
	rimShader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.8f, 0.8f, 0.8f, 1.0f); //sets our background colour
	
//	linkFogShader();
	//linkToon();
//	linkRimLighting();
//	linkReflection();

	

	transformMonkey.SetPos(glm::vec3(-1.5, -sinf(counter), -2.0));
	transformMonkey.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transformMonkey.SetScale(glm::vec3(0.6, 0.6, 0.6));

	reflectionShader.Bind();
	linkReflection();
	reflectionShader.Update(transformMonkey, myCamera);

	monkeyMesh.draw();
	monkeyMesh.updateSphereData(*transformMonkey.GetPos(), 0.62f);

	transformBanana.SetPos(vec3(0.0, 0.0, 2.0));
	transformBanana.SetRot(vec3(0.0, 0.0, 0.0));
	transformBanana.SetScale(vec3(0.01, 0.01, 0.01));

	//toonShader.Bind();
	//linkToon();
	//toonShader.Update(transformBanana, myCamera);

	customShader.Bind();
	linkCustomShader();
	customShader.Update(transformBanana, myCamera);

	//bananaTexture.Bind(0);
	bananaMesh.draw();
	bananaMesh.updateSphereData(*transformBanana.GetPos(), 0.62f);

	transformSword.SetPos(vec3(2.0, 1 + sinf(counter), 0.0));
	transformSword.SetRot(vec3(-90.0, counter * 5, 0.0));
	transformSword.SetScale(vec3(0.05, 0.05, 0.05));

	geoShader.Bind();
	linkGeo();
	geoShader.Update(transformSword, myCamera);
	//swordTexture.Bind(0);

	//customShader.Bind();
	//swordTexture.Bind(0);
	//geoShader.Update(transformSword, myCamera);

	swordMesh.draw();
	swordMesh.updateSphereData(*transformSword.GetPos(), 0.62f);

	counter = counter + 0.01f;

	skybox.draw(&myCamera);	
	

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();


	_gameDisplay.swapBuffer();	
	

} 