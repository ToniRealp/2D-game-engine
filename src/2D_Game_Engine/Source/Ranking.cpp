#include "../Headers/Ranking.h"


Ranking::Ranking(std::vector<std::pair<std::string, int>> &ranking)
{
	tag = "ranking";
	sceneState = SceneState::RUNNING;
		
	renderOrder.push_back(new Background(Rect(Vec2(0, 0), Vec2(SCREEN_WIDTH, SCREEN_HEIGHT)), Texture("Bg", "../../res/img/Backgroung.jpg"), &gameObjects));
	
	for (int i = 0; i < ranking.size(); i++) 
	{
		std::stringstream id, score;
		id << "Rank" << i;
		score << ranking[i].second;
		
		renderOrder.push_back(new TextGO(Rect(100, 30 + i * (SCREEN_HEIGHT - 100) / 12, 120, 40), &gameObjects,
			Text({ 255,255,255,255 }, id.str(), std::to_string(i + 1) + ".  " + ranking[i].first + ":		" + score.str()), Font("sunspire", "../../res/ttf/sunspire.ttf", 80)));
	}
	
	gameObjects["exitButton"] = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "exitNormal", "exit"),
		Text(Color(0, 150, 255, 255), "exitHover", "Exit"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "mouse");
	
	gameObjects["mouse"] = new Mouse(Rect(Vec2(0, 0), Vec2(60, 20)), Texture("platform", "../../res/img/platform.png"), &gameObjects);
	
}

Ranking::~Ranking()
= default;

void Ranking::Update()
{
	for (auto &t : gameObjects) {
		t.second->Update();
	}
	if (gameObjects["exitButton"]->GetCollider()->Collides(*gameObjects["mouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked || Input::ESC)
		sceneState = SceneState::EXIT;
}

void Ranking::Render()
{
	for (auto& g : renderOrder)
	{
		g->Render();
	}
	gameObjects.at("exitButton")->Render();
	gameObjects.at("mouse")->Render();

}

