#include "DynText.h"


DynText::DynText(Rect _rect,const GameObjects * _gameObjects, Player * _player, Font _font, std::string _tag):GameObject(_rect, Texture("platform", "../../res/img/platform.png"), _gameObjects, _tag),
player(_player),font(_font)
{
	score = player->GetScore();
	std::stringstream id,punt;
	id << "punt" << player->GetPlayerNum();
	punt << "PL" << player->GetPlayerNum() << ": " << score;
	texture.id = id.str();

	renderer->LoadFont(font);
	renderer->LoadTextureText(font.id, Text(Color(255, 0, 0, 255), texture.id, punt.str()));
}

DynText::~DynText()
{
	player = nullptr;
}

void DynText::Update()
{
	if (player->GetScore() != score) 
	{
		score = player->GetScore();
		std::stringstream id, punt;
		id << "punt" << player->GetPlayerNum();
		punt << "PL" << player->GetPlayerNum() << ": " << score;

		renderer->LoadTextureText(font.id, Text(Color(255, 0, 0, 255), texture.id, punt.str()));
	}

	score = player->GetScore();
}
