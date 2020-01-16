#include "../Headers/Play.h"


Play::Play(bool *_music, std::vector<std::pair<std::string, int>> *_ranking, int &_lowestScore):frameStart(0), frameTime(0),music(_music),ranking(_ranking),lowestScore(_lowestScore)
{
	numPowerUps = 0;
	tag = "Play";
	sceneState = SceneState::RUNNING;
	playState = PlayState::START;

	// Carga de bricks
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();
	Vec2 n(std::atoi(pRoot->first_node("BrickInfo")->first_node("Normal")->first_attribute("min")->value()), std::atoi(pRoot->first_node("BrickInfo")->first_node("Normal")->first_attribute("max")->value()));
	Vec2 h(std::atoi(pRoot->first_node("BrickInfo")->first_node("Heavy")->first_attribute("min")->value()), std::atoi(pRoot->first_node("BrickInfo")->first_node("Heavy")->first_attribute("max")->value()));
	int movSpeed = std::atoi(pRoot->first_node("Level")->first_attribute("PlatformSpeed")->value());

	gameObjects["background"] = new Background(Rect(Vec2(0, 0), Vec2(SCREEN_WIDTH, SCREEN_HEIGHT)), Texture("Bg", "../../res/img/Backgroung.jpg"), &gameObjects,"nonCollidable");
	gameObjects["topCollider"] = new Collider({-100,0,SCREEN_WIDTH+200,20},  &gameObjects);
	gameObjects["bottomCollider"] = new Collider({ -100,SCREEN_HEIGHT-130,SCREEN_WIDTH+200,20 }, &gameObjects);
	gameObjects["rightCollider"] = new Collider({ SCREEN_WIDTH - 20,-100,20,SCREEN_HEIGHT+200}, &gameObjects);
	gameObjects["leftCollider"] = new Collider({ 0,-100,20,SCREEN_HEIGHT+200}, &gameObjects);
	gameObjects["player1"] = new Player(Rect(Vec2(40, (SCREEN_HEIGHT-130)/2), Vec2(60, 20)), Texture("player", "../../res/img/platform.png"), &gameObjects,"player",1, movSpeed);
	gameObjects["player2"] = new Player(Rect(Vec2(700, (SCREEN_HEIGHT - 130) / 2), Vec2(60, 20)), Texture("player", "../../res/img/platform.png"), &gameObjects,"player",2, movSpeed);
	gameObjects["ball"] = new Ball(Rect(100, (SCREEN_HEIGHT - 130) / 2, 20, 20), Texture("ball", "../../res/img/ball.png"), &gameObjects);
	gameObjects["score1"] = new DynText(Rect(100, 500, 140, 60), &gameObjects, dynamic_cast<Player*> (gameObjects["player1"]), Font("sunspire", "../../res/ttf/sunspire.ttf", 80),"nonCollidable");
	gameObjects["score2"] = new DynText(Rect(490, 500, 140, 60), &gameObjects, dynamic_cast<Player*> (gameObjects["player2"]), Font("sunspire", "../../res/ttf/sunspire.ttf", 80),"nonCollidable");
	
	for (rapidxml::xml_node<> *pNode = pRoot->first_node("Level")->first_node("Brick"); pNode; pNode = pNode->next_sibling()) {
			int i, j, type, score;
			BrickType b;
			std::stringstream id,v;
			i = std::atoi(pNode->first_attribute("i")->value());
			j = std::atoi(pNode->first_attribute("j")->value());
			id << "brick" << i << j;
			v << pNode->first_attribute("type")->value();
			if (v.str()=="N")
			{
				type = 0;
				score = rand() % (n.y + 1 - n.x) + n.x;
				b = BrickType::NORMAL;
			}
			else if (v.str() == "H")
			{
				type = 1;
				score = rand() % (h.y + 1 - h.x) + h.x;
				b = BrickType::HEAVY;
			}
			else if (v.str() == "F")
			{
				type = 2;
				score = 0;
				b = BrickType::FIX;
			}
			gameObjects[id.str()] = new Brick(Rect(SCREEN_WIDTH / 2 + (j - 6) * 20, ((SCREEN_HEIGHT-130) / 2 + (i - 5.5f) * 40)+20, 40, 20), Texture("brick", "../../res/img/bricks.jpg"), &gameObjects, "brick", score, b);
	}
	
	gameObjects["start"] = new TextGO(Rect(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 100, 500, 100), &gameObjects,
		Text({ 255,255,255,255 }, "startText", "Press spacebar to start game"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80));

	for (auto &t : gameObjects) {
		t.second->UpdateGameObjects(&gameObjects);
	}
}

Play::~Play()
= default;

void Play::Update()
{
	switch (playState)
	{
	case Play::PlayState::START:

		if (Input::ESC)
			sceneState = SceneState::EXIT;
		if (Input::SPACE) {
			gameObjects.erase("start");
			playState = PlayState::PLAYING;
		}

		break;

	case Play::PlayState::PLAYING:

		frameStart = clock();
		for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
			if (it->second->deleteMe)
			{
				if (it->second->GetTag() == "brick") 
				{
					int random = rand() % 100;
					if (random<20)
					{
						numPowerUps++;
						std::stringstream str;
						str << "powerUp" << numPowerUps;
						gameObjects[str.str()] = new PowerUps(Rect(it->second->GetRect().position, Vec2(60, 20)), Texture("player", "../../res/img/platform.png"), &gameObjects, dynamic_cast<Ball*>(gameObjects["ball"])->GetLastTouched());
					}
				}
				auto aux = it;
				it--;
				gameObjects.erase(aux);
			}
		}
		for (auto &t : gameObjects) {
			t.second->Update();
		}

		if (dynamic_cast<Player*>(gameObjects["player1"])->GetHealth() == 0 || dynamic_cast<Player*>(gameObjects["player2"])->GetHealth() == 0)
		{
			playState = PlayState::GAMEOVER;
			gameObjects["zgameOver"] = new TextGO(Rect(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 100, 500, 100), &gameObjects,
				Text({ 255,255,255,255 }, "gameOverText", "GAME OVER"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80));

		}
		else if (dynamic_cast<Ball*>(gameObjects["ball"])->GetSpawn())
		{
			gameObjects["start"] = new TextGO(Rect(SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 100, 500, 100), &gameObjects,
				Text({ 255,255,255,255 }, "startText", "Press spacebar to start game"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80));
			playState = PlayState::START;
			dynamic_cast<Ball*>(gameObjects["ball"])->SetSpawn();

		}

		if (Input::ESC||Input::P) {
			playState = PlayState::PAUSE;
			gameObjects["zmouse"] = new Mouse(Rect(Vec2(0, 0), Vec2(60, 20)), Texture("platform", "../../res/img/platform.png"), &gameObjects);
			gameObjects["resume"] = new Button({ 100, 60,200, 80 }, &gameObjects, Text(Color(255, 150, 0, 255), "resumeNormal", "Resume"),
				Text(Color(0, 150, 255, 255), "resumeHover", "Resume"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
			if (*music)
			{
				gameObjects["musicButton"] = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOn", "sound on"),
					Text(Color(0, 150, 255, 255), "soundOnHover", "sound on"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
			}
			else
			{
				gameObjects["musicButton"] = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOff", "sound off"),
					Text(Color(0, 150, 255, 255), "soundOffHover", "sound off"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
			}
			
		}

		frameTime = clock() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
		break;

	case Play::PlayState::PAUSE:

		gameObjects["zmouse"]->Update();
		gameObjects["resume"]->Update();
		gameObjects["musicButton"]->Update();

		if (Input::ESC) {
			sceneState = SceneState::EXIT;
		}
		else if (Input::SPACE || Input::P || (gameObjects["resume"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked)) {
			//delete gameObjects["resume"];
			//delete gameObjects["zmouse"];
			gameObjects.erase("resume");
			gameObjects.erase("zmouse");
			gameObjects.erase("musicButton");
			playState = PlayState::PLAYING;
		}
		else if (gameObjects["musicButton"]->GetCollider()->Collides(*gameObjects["zmouse"]->GetCollider()) != Tools::CollSide::NONE && Input::isClicked)
		{
			if (*music)
			{
				Mix_PauseMusic();
				delete gameObjects.at("musicButton");
				gameObjects.erase("musicButton");
				gameObjects["musicButton"] = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOff", "sound off"),
					Text(Color(0, 150, 255, 255), "soundOffHover", "sound off"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
				*music = false;
			}
			else
			{
				Mix_ResumeMusic();
				delete gameObjects["musicButton"];
				gameObjects.erase("musicButton");
				gameObjects["musicButton"] = new Button(Rect(Vec2(500, 350), Vec2(200, 80)), &gameObjects, Text(Color(255, 150, 0, 255), "soundOn", "sound on"),
					Text(Color(0, 150, 255, 255), "soundOnHover", "sound on"), Font("sunspire", "../../res/ttf/sunspire.ttf", 80), "zmouse");
				*music = true;
			}
		}
		break;
	case PlayState::GAMEOVER:
		if (Input::ESC || Input::SPACE) {
			playState = PlayState::RANKING;
		}
			break;
	case PlayState::RANKING:
		std::cout << "Insert your name:" << std::endl;
		std::cin >> name;
		if (dynamic_cast<Player*>(gameObjects["player1"])->GetScore() > dynamic_cast<Player*>(gameObjects["player2"])->GetScore())
			score = dynamic_cast<Player*>(gameObjects["player1"])->GetScore();
		else
			score = dynamic_cast<Player*>(gameObjects["player2"])->GetScore();
		UpdateRanking(name, score);
		sceneState = SceneState::EXIT;
		break;
	default:
		break;
	}
}

void Play::UpdateRanking(std::string name, int score)
{
	if (ranking->size() == 0)
		ranking->push_back({ name,score });
	else
	{
		if (ranking->size() >= 10)
		{
			if (score > lowestScore)
			{
				ranking->pop_back();
				for (auto it = ranking->begin(); it != ranking->end(); it++)
				{
					if (score > it->second)  ranking->insert(it, { name, score });
					break;
				}
			}
		}
		else
		{
			bool inserted = false;
			for (auto it = ranking->begin(); it != ranking->end(); it++)
			{
				if (score > it->second)
				{
					ranking->insert(it, { name, score });
					inserted = true;
					break;
				}
			}
			if (!inserted)
				ranking->push_back({ name, score });
		}
	}
}
