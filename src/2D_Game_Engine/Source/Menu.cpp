#include "../Headers/Menu.h"


Menu::Menu(bool *_music):music(_music)
{
	tag = "Menu";
	sceneState = SceneState::RUNNING;
	//renderer = Renderer::Instance();

	gameObjects["background"]=new Background(Rect(Vec2(0, 0), Vec2(SCREEN_WIDTH, SCREEN_HEIGHT)), Texture("Bg", "../../res/img/Backgroung.jpg"),&gameObjects);
	gameObjects["playButton"] = new Button(Rect(Vec2(100, 60), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "playNormal", "play"),
		Text(Color(0, 150, 255, 255), "playHover", "Play"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
	gameObjects["prankingButton"] = new Button(Rect(Vec2(100, 200), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "rankingNormal", "ranking"),
		Text(Color(0, 150, 255, 255), "rankingHover", "ranking"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80),"zmouse");
	gameObjects["exitButton"] = new Button(Rect(Vec2(100, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "exitNormal", "exit"),
		Text(Color(0, 150, 255, 255), "exitHover", "Exit"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
	gameObjects["musicButton"] = musicOn = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOn", "sound on"),
		Text(Color(0, 150, 255, 255), "soundOnHover", "sound on"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
	musicOff = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOff", "sound off"),
		Text(Color(0, 150, 255, 255), "soundOffHover", "sound off"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
	gameObjects["zmouse"] = new Mouse(Rect(Vec2(0, 0), Vec2(60, 20)), Texture("platform", "../../res/img/platform.png"), &gameObjects);


	for (auto &t : gameObjects) {
		t.second->UpdateGameObjects(&gameObjects);
	}

}

Menu::~Menu()
{
	delete musicOn;
	delete musicOff;
}


void Menu::Update()
{
	for (auto &t : gameObjects) {
		t.second->Update();
	}
	if (gameObjects["exitButton"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked||Input::ESC)
		sceneState = SceneState::EXIT;
	if (gameObjects["playButton"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider())!=Tools::CollSide::NONE && Input::isClicked)
		sceneState = SceneState::PLAY;
	if (gameObjects["prankingButton"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked)
		sceneState = SceneState::RANKING;
	if (gameObjects["musicButton"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked)
	{
		if (*music)
		{
			Mix_PauseMusic();
			gameObjects["musicButton"] = musicOff;
			*music = false;
		}
		else 
		{
			Mix_ResumeMusic();
			gameObjects["musicButton"] = musicOn;
			*music = true;
		}
		
	}

}