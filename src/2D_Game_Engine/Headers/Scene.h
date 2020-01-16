#pragma once
#include <unordered_map>
#include "Constants.h"
#include "GameObject.h"
#include "Background.h"
#include "Renderer.h"
#include "Input.h"
#include "TextGO.h"
#include <SDL_mixer.h>

enum class SceneState { RUNNING, PLAY, RANKING, EXIT};

class Scene
{
protected:

	std::string tag;
	GameObjects gameObjects;
	SceneState sceneState;
	

public:
	Scene();
	~Scene();

	SceneState GetSceneState();
	std::string GetTag();
	virtual void Render();
	virtual void Update() = 0;
};

