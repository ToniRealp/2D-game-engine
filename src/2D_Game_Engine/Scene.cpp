#include "Scene.h"


Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto &t : gameObjects) {
		delete t.second;
	}
	gameObjects.clear();
}

SceneState Scene::GetSceneState() { return sceneState; }
std::string Scene::GetTag() { return tag; }

void Scene::Render()
{
	for (auto &t : gameObjects) {
		t.second->Render();
	}
}