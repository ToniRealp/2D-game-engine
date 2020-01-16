#pragma once
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"
#include "SplashScreen.h"
#include <SDL_mixer.h>

class GameContoller
{
private:
	Scene *currentScene;
	bool playing;
	Renderer *renderer;
	SDL_Event event;
	bool music = true;

	void LoadRanking();
	void SaveRanking();
	std::vector<std::pair<std::string, int>> ranking;
	
	int lowestScore;

public:
	GameContoller();
	~GameContoller();
	void Update();
};