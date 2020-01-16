#include "../Headers/GameContoller.h"

GameContoller::GameContoller(){

	playing = true;
	currentScene = new SplashScreen();
	renderer = Renderer::Instance();

	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)&mixFlags))throw "error SDL_mixer";

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		throw "Unable to initialize sdl_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/Arkanoid.mp3") };
	if (!soundtrack) throw "Unable to laoasd the mix music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	LoadRanking();
}

GameContoller::~GameContoller()
{
	delete renderer;
	delete currentScene;
}

void GameContoller::Update()
{

	while (playing)
	{
		renderer->Clear();
		Input::ESC = false;
		Input::P = false;
		Input::SPACE = false;
		Input::isClicked = false;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				playing = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) Input::ESC = true;
				if (event.key.keysym.sym == SDLK_w) Input::W = true;
				if (event.key.keysym.sym == SDLK_a) Input::A = true;
				if (event.key.keysym.sym == SDLK_s) Input::S = true;
				if (event.key.keysym.sym == SDLK_d) Input::D = true;
				if (event.key.keysym.sym == SDLK_p) Input::P = true;
				if (event.key.keysym.sym == SDLK_UP) Input::UP = true;
				if (event.key.keysym.sym == SDLK_LEFT) Input::LEFT = true;
				if (event.key.keysym.sym == SDLK_DOWN) Input::DOWN = true;
				if (event.key.keysym.sym == SDLK_RIGHT) Input::RIGHT = true;
				if (event.key.keysym.sym == SDLK_SPACE) Input::SPACE = true;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_w)Input::W = false;
				if (event.key.keysym.sym == SDLK_a) Input::A = false;
				if (event.key.keysym.sym == SDLK_s) Input::S = false;
				if (event.key.keysym.sym == SDLK_d) Input::D = false;
				if (event.key.keysym.sym == SDLK_UP) Input::UP = false;
				if (event.key.keysym.sym == SDLK_LEFT) Input::LEFT = false;
				if (event.key.keysym.sym == SDLK_DOWN) Input::DOWN = false;
				if (event.key.keysym.sym == SDLK_RIGHT) Input::RIGHT = false;
				break;
			case SDL_MOUSEMOTION:
				Input::mousePos = { event.motion.x, event.motion.y };
				break;
			case SDL_MOUSEBUTTONDOWN:
				Input::isClicked = true;
				break;

			default:;
			}

		}

		switch (currentScene->GetSceneState())
		{
		case SceneState::RUNNING:
			currentScene->Update();
			currentScene->Render();
			break;

		case SceneState::PLAY:
			delete(currentScene);
			currentScene = new Play(&music,&ranking,lowestScore);
			break;

		case SceneState::EXIT:
			if (currentScene->GetTag() == "Menu")
				playing = false;
			if (currentScene->GetTag() == "Play")
			{
				delete currentScene;
				currentScene = new Ranking(ranking);
			}
			else
			{
				delete(currentScene);
				currentScene = new Menu(&music);
			}

			break;
		case SceneState::RANKING:
			delete(currentScene);
			currentScene = new Ranking(ranking);
			break;
		default:
			break;
		}

		renderer->Render();

	}
}
void GameContoller::LoadRanking()
{

	std::string name;
	size_t size, rankSize;
	int score;

	try
	{
		std::fstream rFile("../../res/files/ranking.bin", std::ios::in | std::ios::binary);

		rFile.read(reinterpret_cast<char*>(&rankSize), sizeof(size_t));
		bool first = true;
		for (size_t i = 0; i < rankSize; i++)
		{
			rFile.read(reinterpret_cast<char*>(&size), sizeof(size_t));
			char *aux = new char[size + 1];
			rFile.read(aux, size);
			aux[size] = '\0';
			name = aux;
			delete aux;

			rFile.read(reinterpret_cast<char*>(&score), sizeof(int));
			if (first)
			{
				lowestScore = score;
				first = false;
			}
			if (score < lowestScore)
				lowestScore = score;
			ranking.push_back({ name, score });
		}
		rFile.close();
	}
	catch (const std::exception& e)
	{
		
	}
}



void GameContoller::SaveRanking()
{
	size_t size;

	std::fstream wFile("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
	size = ranking.size();
	wFile.write(reinterpret_cast<char*>(&size), sizeof(size_t));
	for (auto &it : ranking)
	{
		size = it.first.size();
		wFile.write(reinterpret_cast<char*>(&size), sizeof(size_t));
		wFile.write(it.first.c_str(), size);
		wFile.write(reinterpret_cast<char*>(&it.second), sizeof(int));
	}

	wFile.close();
}


