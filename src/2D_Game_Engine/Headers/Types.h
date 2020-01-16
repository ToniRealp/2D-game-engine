#pragma once
#include <math.h>
#include <iostream>
#include <string>

	struct Vec2
	{
		int x;
		int y;

		Vec2(int _x, int _y):x(_x),y(_y){}

		void operator+=(Vec2 vec) {
			(this->x += vec.x, this->y += vec.y);
		}

	};

	inline
	Vec2 operator* (Vec2 vec, int i) 
	{
		return Vec2(vec.x * i, vec.y * i);
	}

	inline
	Vec2 operator* (Vec2 vec, float i) 
	{
		return Vec2(vec.x * i, vec.y * i);
	}

	struct FVec2
	{
		float x;
		float y;
		FVec2(float _x, float _y) :x(_x), y(_y){}

	};

	inline
	FVec2 operator* (FVec2 vec, float i) 
	{
		return FVec2(vec.x * i, vec.y * i);
	}

	inline
		FVec2 operator- (FVec2 vec, FVec2 vec2)
	{
		return FVec2(vec.x -vec2.x , vec.y - vec2.y);
	}

	inline
		FVec2 operator+ (FVec2 vec, FVec2 vec2)
	{
		return FVec2(vec.x + vec2.x, vec.y + vec2.y);
	}

	inline
		Vec2 operator+ (Vec2 vec, Vec2 vec2)
	{
		return Vec2(vec.x + vec2.x, vec.y + vec2.y);
	}

	inline
	Vec2 operator+(Vec2 vec2, FVec2 vec)
	{
		return(Vec2(vec2.x + static_cast<int>(vec.x), vec2.y + static_cast<int>(vec.y)));
	}

	struct Line 
	{
		int pInicial;
		int pFinal;
	};

	struct Rect 
	{
		Vec2 position;
		Vec2 size;
		Rect(Vec2 _pos, Vec2 _size) :position(_pos), size(_size) {}
		Rect(int posx, int posy, int sizex, int sizey) :position(posx, posy), size(sizex, sizey) {};
	};

	struct Circle 
	{
		Vec2 position;
		float radius;
		Circle(Vec2 _position, float _radius):position(_position), radius(_radius){}
		Circle(int posx, int posy, float _radius) :position(posx, posy), radius(_radius) {}
	};

	struct Font 
	{
		std::string id;
		std::string path;
		int size;
		Font(std::string _id, std::string _path, int _size):id(_id), path(_path), size(_size) {}
	};

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		Color(int _r, int _g, int _b, int _a) :r(_r), g(_g), b(_b), a(_a) {}
	};

	struct Text 
	{
		Color color;
		std::string id;
		std::string text;
		Text(Color _color, std::string _id, std::string _text) :color(_color), id(_id), text(_text) {}
	};

	struct Texture 
	{
		std::string id;
		std::string path;

		Texture(std::string _id, std::string _path):id(_id),path(_path) {}
	};