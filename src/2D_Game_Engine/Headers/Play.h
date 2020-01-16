#pragma once
#include "Scene.h"
#include "Collider.h"
#include "Player.h"
#include "Ball.h"
#include "DynText.h"
#include "Brick.h"
#include "Button.h"
#include "Mouse.h"
#include "TextGO.h"
#include "PowerUps.h"
#include <iostream>
#include <sstream>
#include "../../../dep/inc/XML/rapidxml.hpp"
#include "../../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../../dep/inc/XML/rapidxml_print.hpp"

class Play :
	public Scene
{
private:

	enum class PlayState {START, PLAYING, PAUSE, GAMEOVER, RANKING};
	const int DELAY_TIME = 1000.0f / 60;
	Uint32 frameStart, frameTime;
	PlayState playState;
	bool *music;
	std::string name;
	int score, lowestScore, numPowerUps;
	std::vector<GameObject*> renderOrder;

	void UpdateRanking(std::string _name, int _points);
	std::vector<std::pair<std::string, int>> *ranking;

public:

	Play(bool*, std::vector<std::pair<std::string, int>> *,int &);
	~Play();
	void Update() override;
};

