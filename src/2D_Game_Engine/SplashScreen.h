#pragma once
#include "Scene.h"
#include <ctime>
class SplashScreen :
	public Scene
{
public:
	SplashScreen();
	~SplashScreen();
private:
	void Update() override;
	time_t start, counter;

};

