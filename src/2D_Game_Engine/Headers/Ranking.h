#pragma once
#include "Scene.h"
#include "TextGO.h"
#include "Button.h"
#include "Mouse.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "../../../dep/inc/XML/rapidxml.hpp"
#include "../../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../../dep/inc/XML/rapidxml_print.hpp"

class Ranking :
	public Scene
{
public:
	Ranking(std::vector<std::pair<std::string, int>> &);
	~Ranking();
	void Update() override;
	void Render() override;
	
private:
	std::vector<GameObject*> renderOrder;
};

