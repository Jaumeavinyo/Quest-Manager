#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "PathFinding.h"
#include "Scene.h"
#include "QuestManager.h"

Scene::Scene() : Module()
{
	name.assign("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	if(myApp->map->Load("hello2.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(myApp->map->CreateWalkabilityMap(w, h, &data))
			myApp->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = myApp->tex->Load("maps/path2.png");

	
	ValidArea.x = 400;
	ValidArea.y = 350;
	ValidArea.w = 200;
	ValidArea.h = 200;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	if (myApp->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		myApp->render->camera.y += 1;
		ValidArea.y -= 1;
	}
		


	if (myApp->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			myApp->render->camera.y -= 1;
			ValidArea.y += 1;
    }
		

	if (myApp->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		myApp->render->camera.x += 1;
		ValidArea.x -= 1;
	}
		

	if (myApp->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		myApp->render->camera.x -= 1;
		ValidArea.x += 1;
	}
		

	//---------------------------------------------GAME--------------------------------------------
	
	
	SDL_Rect Area;
	Area.x = 10;
	Area.y = 10;
	Area.w = 10000;
	Area.h = 10000;

	
	
	myApp->render->DrawQuad(Area, 255, 255, 255, 255, true, true);
	myApp->render->DrawQuad(ValidArea, 0, 0, 0, 150, true, true);
	


	//---------------------------------------------GAME--------------------------------------------
	for (std::list <Quest*>::iterator it = myApp->quests->preparedQuests.begin(); it != myApp->quests->preparedQuests.end(); it++) {
		
		if ((*it)->activationEvent->type == MOVEMENT_EVENT && ((*it)->activationEvent->Object.x - ValidArea.x)<100 && ((*it)->activationEvent->Object.x - ValidArea.x)>-100 && ((*it)->activationEvent->Object.y - ValidArea.y) < 150 && ((*it)->activationEvent->Object.y - ValidArea.y) > -150) {
			(*it)->activationEvent->completed = true;
			LOG("ACTIVATION EVENT COMPLETED");
			myApp->quests->activatedQuests.push_back((*it));
		}	
	}
	for (std::list <Quest*>::iterator it = myApp->quests->activatedQuests.begin(); it != myApp->quests->activatedQuests.end(); it++) {
		
		for (std::list<Event*>::iterator it_= (*it)->subMissions.begin(); it_ != (*it)->subMissions.end(); it_++) {
			LOG("SECUNDARY EVENT COMPLETED");
			if ((*it_)->type == MOVEMENT_EVENT && ((*it_)->Object.x - ValidArea.x) < 100 && ((*it_)->Object.x - ValidArea.x) > -100 && ((*it_)->Object.y - ValidArea.y) < 150 && ((*it_)->Object.y - ValidArea.y) > -150) {
				
				LOG("SECUNDARY EVENT COMPLETED");
			}
			
		}
	}
	//myApp->quests->activatedQuests.
	//myApp->render->DrawQuad(, 255, 0, 255, alpha);

	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.h = 10000;
	rect.w = 10000;

	myApp->map->Draw();
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(myApp->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}