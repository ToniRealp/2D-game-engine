#include "../Headers/TextGO.h"


TextGO::TextGO(Rect _rect, const GameObjects * _gameObjects, Text _normalTexture, Font _font):
	GameObject(_rect,Texture("platform","../../res/img/platform.png"),gameObjects),font(_font)
{
	renderer->LoadFont(_font);
	renderer->LoadTextureText(font.id, _normalTexture);
	texture.id = _normalTexture.id;
}

TextGO::~TextGO()
{
}

void TextGO::Update()
{
}
