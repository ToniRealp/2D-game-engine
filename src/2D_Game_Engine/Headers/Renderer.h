#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <unordered_map>
#include "Constants.h"
#include "Types.h"


class Renderer {

private:
	SDL_Renderer *m_renderer = nullptr;
	SDL_Window *m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	static Renderer *renderer;
	Renderer();

public:
	static Renderer *Instance()
	{
		if (renderer == nullptr) { renderer = new Renderer; }
		return renderer;
	};

	~Renderer();
	 void Clear()  ;
	 void Render() ;
	 void LoadFont(Font font);
	 void LoadTexture(const Texture &_texture);
	 void LoadTextureText(const std::string &fontId, Text text);
	 Vec2 GetTextureSize(const std::string &id);
	 void PushImage(const std::string &id,const Rect &rect);
	 void PushRotatedImage(const std::string &id, const Rect &rect, float angle);
	 void PushSprite(const std::string &id,const Rect &rectSprite,const Rect &rectPos);
	 void PushRotatedSprite(const std::string &id, const Rect rectSprite, const Rect rectPos, float angle);
	 void SetRendreDrawColor(int r, int g, int b);	 
};


