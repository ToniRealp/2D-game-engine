#pragma once
#include "GameObject.h"
class TextGO :
	public GameObject
{
public:
	TextGO(Rect _rect, const GameObjects * _gameObjects, Text _normalTexture, Font font);
	~TextGO();
	void Update() override;
private:
	Font font;
};

