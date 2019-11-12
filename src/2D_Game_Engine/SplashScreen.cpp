#include "SplashScreen.h"



SplashScreen::SplashScreen()
{
	tag = "splashScreen";
	sceneState = SceneState::RUNNING;
	gameObjects["background"] = new Background(Rect(Vec2(0, 0), Vec2(SCREEN_WIDTH, SCREEN_HEIGHT)), Texture("Bg", "../../res/img/Backgroung.jpg"), &gameObjects);
	gameObjects["title"] = new Background(Rect(Vec2(100, 100), Vec2(600, 200)), Texture("arkanoid", "../../res/img/Arkanoid-logo.png"), &gameObjects);
	start = std::clock();
}


SplashScreen::~SplashScreen()
{}

void SplashScreen::Update()
{
	counter = (std::clock()-start)/CLOCKS_PER_SEC;
	if (counter >= 3)
		sceneState = SceneState::EXIT;
}
