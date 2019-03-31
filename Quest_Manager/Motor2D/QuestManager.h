#ifndef QUEST_MANAGER_H_
#define QUEST_MANAGER_H_

#include "Module.h"
#include "Point.h"
#include <vector>
#include <list>
#include "SDL/include/SDL_rect.h"


enum  EVENT_TYPE {
	MOVEMENT_EVENT = 0
};
//___________________________________________________

class  Event
{
public:
	Event(EVENT_TYPE type_) :type(type_) {};
	~Event();
	EVENT_TYPE type;
	int orderNumber; //if it its value is -1 you can do thgis mission without following any order
	SDL_Rect Object;
	bool completed = false;
};  
//___________________________________________________
class MovementEvent: public Event {
public: 
	MovementEvent():Event(EVENT_TYPE::MOVEMENT_EVENT){}
	~MovementEvent(){}	
};
//___________________________________________________
class Quest
{
public:
	Quest() {};
	~Quest();
	
	int DNI; //just to identify every quest by a number (just in case you want to acces a quest in a future)
	int Reward;
	Event* activationEvent;
	std::list <Event*> subMissions;

private:
	
};
//___________________________________________________

class Quest_Manager : public Module {
public:
	Quest_Manager();
	~Quest_Manager();

	bool Awake(pugi::xml_node& file);
	bool Start();
	Event* createEvent(pugi::xml_node&);

	void ActivateNextQuest(){}
	
	pugi::xml_document xmlfile;

	std::list<Quest*> preparedQuests; //quest that are not active because the trigger hasn't been triggered
	std::list<Quest*> activatedQuests; //active quests that you can complete
	std::list<Quest*> endedQuests; //done quests. You can not use this list and just destroy quests when finished
};
//___________________________________________________




#endif
