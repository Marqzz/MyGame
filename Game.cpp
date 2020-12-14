#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
/*#include "GameObject.h"
//#include "ECS.h"
//include "Components.h"
//GameObject* player;
//GameObject* enemy;
//We have to create a map , then tell the game to render it
SDL_Texture* playerTex;
SDL_Rect srcR, destR;//sourceRectangle - de unde pleaca , destinationRectangle - unde ajunge
//nu mai avem nevoie de alea de sus pt ca avem GameObject class , cu functia de update ( deplasare ? )
*/
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"


SDL_Renderer* Game::renderer = nullptr;//initializem staticul renderer
SDL_Event Game::event;//now we can access this event

SDL_Rect Game::camera = { 0,0,800,640 };

Map* map;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());//that will create our player for us
auto& wall(manager.addEntity());//that will create a collision object

const char* mapfile = "assets/terrain_ss.png";

//auto& tile0(manager.addEntity());
//auto& tile1(manager.addEntity());
//auto& tile2(manager.addEntity());

enum groupLabels : std::size_t
{
	//now we can name some of our groups
	//group labels efectiv din nume suggestion
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;//pt fullscreen sau windowed

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	/*player = new GameObject("assets/player.png",0,0);
	texturesheet ul in cazul asta este poza cu player , noi practic vrem sa creeam pixelii pe ecran
	//playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
	// mai jos avem varianta mai tribala , noi acum am pus treaba de mai jos
	//intr-o functie ( pe care s-ar putea sa o folosim mai departe 
	SDL_Surface* tmpSurface = IMG_Load("assets/player.png");
	playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	//enemy = new GameObject("assets/enemy.png", 75, 75);
	//newPlayer.addComponent<PositionComponent>();
	//will give us acces to position variables*/
	map = new Map();

	//ECS implementation

	//Map::LoadMap("assets/p16x16.map", 16, 16);
	Map::LoadMap("assets/map.map", 25, 20);


	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("assets/player_anims.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//wall.addComponent<SpriteComponent>("assets/dirt.png");
	//wall.addComponent<ColliderComponent>("wall");
	//wall.addGroup(groupMap);
	//tile0.addComponent<TitleComponent>(200, 200, 32, 32, 0);// that 0 at the end means that we have water
	//tile1.addComponent<TitleComponent>(250, 250, 32, 32, 1);//1-dirt
	//tile1.addComponent<ColliderComponent>("dirt");
	//tile2.addComponent<TitleComponent>(150, 150, 32, 32, 2);//2-grass
	//tile2.addComponent<ColliderComponent>("grass");
}


void Game::handleEvents()
{
	//SDL_Event event;
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	/*cnt++;
	destR.h = 128;//inaltimea;
	destR.w = 256;//width-latimea cum ar veni;
	destR.x = cnt;//il folosim ca sa se miste spre stanga

	std::cout << cnt << std::endl; // nu mai avem nevoie pt ca avem metoda din GameObject class care face updateuri la fiecare obiect in parte, daca apelam 
	/*player->Update();
	enemy->Update();
	manager.update();//will update our entities , wich will update all our components
	std::cout << newPlayer.getComponent<PositionComponent>().x() << " , " << newPlayer.getComponent<PositionComponent>().y() << std::endl;*/
	manager.refresh();
	manager.update();
	//mai jos facem ca sa dam swap unor texturi , in cazul unor conditii indeplinite
	//player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	//if (player.getComponent<TransformComponent>().position.x > 100)
	//{
	//	player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
	//if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		//wall.getComponent<ColliderComponent>().collider))
	//{
		//player.getComponent<TransformComponent>().scale = 1;//folosim linia asta ca atunci cand player-ul da collide la ceva collidable , se micsoreaza ( scale = 1 )
		//player.getComponent<TransformComponent>().velocity * -1;//when the player gets hit , we reverse the velocity , so it bounces back
		//std::cout << "wall hit !..." << std::endl;
	//}

	/*Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	//for (auto cc : colliders)
	//{
	//	Collision::AABB(player.getComponent<ColliderComponent>(), * cc);
	//}

	//now need to update the position of the tiles
	for (auto t : tiles)
	{
		// -(pVel.x * pSpeed) ca sa dea senzatia de " mers " ; de asta acel " - "
		t->getComponent<TitleComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TitleComponent>().destRect.y += -(pVel.y * pSpeed);
	}*/

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	//for camera positioning on the player we also need to take away half of the screen so it can leave our player in the middle 
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//checking "bounds"??
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)//camera.w --> the width of our map
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
}

//that will pass ALL of our tiles in the groupMap
//auto& tiles(manager.getGroup(groupMap));
//auto& players(manager.getGroup(groupPlayers));
//auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);
	/*SDL_RenderCopy(renderer, playerTex, NULL, &destR);//primul NULL - toata imaginea , al 2 lea NULL , whole render frame
	// we need to draw our map , and then place enemys there
	/*enemy->Render();
	player->Render();
	//map->DrawMap();
	manager.draw(); <---that used to draw all of our object in the order that we created them*/

	//now we render each group one after another
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

//void Game::AddTile(int id, int x, int y)
void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	//tile.addComponent<TitleComponent>(x, y, 32, 32, id);
	tile.addComponent<TitleComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}
