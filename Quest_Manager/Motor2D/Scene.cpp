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
	position.x = 400;
	ValidArea.y = 350 ;
	position.y = 350;
	ValidArea.w = 50;
	ValidArea.h = 50;

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
		
	}
		


	if (myApp->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			myApp->render->camera.y -= 1;
			
    }
		

	if (myApp->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		myApp->render->camera.x += 1;
		
	}
		

	if (myApp->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		myApp->render->camera.x -= 1;
		
	}
	


	if (myApp->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		
		position.y -= 0.2;
	}
	if (myApp->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		
		position.y += 0.2;
	}
	if (myApp->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
	
		position.x -= 0.2;
	}
	if (myApp->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		
		position.x += 0.2;
	}

	//---------------------------------------------GAME--------------------------------------------
	ValidArea.x = (int)position.x;
	ValidArea.y = (int)position.y;
	
	SDL_Rect Area;
	Area.x = -1000;
	Area.y = 10;
	Area.w = 10000;
	Area.h = 10000;

	
	
	myApp->render->DrawQuad(Area, 255, 255, 255, 255, true, true);
	myApp->render->DrawQuad(ValidArea, 0, 0, 0, 150, true, true);
	
	if (myApp->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
		LOG("SPACEEEE");
	}

	//---------------------------------------------GAME--------------------------------------------
	//LOOKING THE PREPARED_QUESTS LIST
	for (std::list <Quest*>::iterator it = myApp->quests->preparedQuests.begin(); it != myApp->quests->preparedQuests.end(); it++) {
		//if the activation event if not completed draw it grey
		if ((*it)->activationEvent->completed == false) {
			myApp->render->DrawQuad((*it)->activationEvent->Object, 255,0, 0, 150, true, true);
		}
		//if you toutch it put in in completed
		if ((*it)->activationEvent->completed == false && (*it)->activationEvent->type == MOVEMENT_EVENT && ((*it)->activationEvent->Object.x - ValidArea.x)<50 && ((*it)->activationEvent->Object.x - ValidArea.x)>-50 && ((*it)->activationEvent->Object.y - ValidArea.y) < 50 && ((*it)->activationEvent->Object.y - ValidArea.y) > -50) {
			(*it)->activationEvent->completed = true;
			
			LOG("ACTIVATION EVENT COMPLETED");
			//move the quest from prepared to activated
			myApp->quests->activatedQuests.push_back((*it));
			myApp->quests->preparedQuests.erase(it);
		}	
	}

	//LOOKING THE ACTIVATED QUESTS
	for (std::list <Quest*>::iterator it = myApp->quests->activatedQuests.begin(); it != myApp->quests->activatedQuests.end(); it++) {
		//DRAWING IN GREEN THE ACTIVATION EVENT ACTIVATED
		myApp->render->DrawQuad((*it)->activationEvent->Object, 0, 255, 0, 150, true, true);
		for (std::list<Event*>::iterator it_= (*it)->subMissions.begin(); it_ != (*it)->subMissions.end(); it_++) {
			//LOOKING IF THERE ARE SUBMISSIONS LEFT
			int counter = 0;
			for (std::list<Event*>::iterator it_ = (*it)->subMissions.begin(); it_ != (*it)->subMissions.end(); it_++) {
				if ((*it_)->completed == false) {
					counter++;
				}
			}
			//IF THERE ARE SUBMISSIONS LEFT
			if (counter != 0) {
				//LOOK IF THE SQUARES ARE INSIDE
				myApp->render->DrawQuad((*it_)->Object, 0, 0, 0, 150, true, true);
				if ((*it_)->completed == false && (*it_)->type == MOVEMENT_EVENT && ((*it_)->Object.x - ValidArea.x) < 50 && ((*it_)->Object.x - ValidArea.x) > -50 && ((*it_)->Object.y - ValidArea.y) < 50 && ((*it_)->Object.y - ValidArea.y) > -50) {
					(*it_)->completed = true;
					LOG("SECUNDARY EVENT COMPLETED");
					
					if (it_ != (*it)->subMissions.end()) {
						(*it)->subMissions.erase(it_);
					}
					if (it_ == (*it)->subMissions.end()) {
						(*it)->subMissions.erase(it_);
						myApp->quests->endedQuests.push_back((*it));
						myApp->quests->activatedQuests.erase((it));
						
					}
				}
			}//MOVE THE QUEST TO ENDED QUESTS
			
		}
	}
	

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

//bool Scene::isInside(SDL_Rect A, SDL_Rect B) {
//
//}