#ifndef QUEST_MANAGER_H_
#define QUEST_MANAGER_H_

#include "Module.h"
#include "Point.h"
#include <vector>
#include <list>
#include "SDL/include/SDL_rect.h"

/*TODO 2:
create an enum called EVENT_TYPE and give a new event called <TOUCH_EVENT>
*/
enum  EVENT_TYPE {
	TOUCH_EVENT = 0
};
//___________________________________________________
/*TODO 0
Class Event is already created, take note about its variables and types, you will need them in the future
*/
class  Event
{
public:
	Event(EVENT_TYPE type_) :type(type_) {};
	~Event();
	EVENT_TYPE type;
	int orderNumber; 
	SDL_Rect Object;
	bool completed = false;
};  
//___________________________________________________
class TouchEvent: public Event {
public: 
	TouchEvent():Event(EVENT_TYPE::TOUCH_EVENT){}
	~TouchEvent(){}
};
//___________________________________________________

/*TODO 1:  
-Create a clas named <Quest> 
-Then ad an integer variable to give every quest an identification number like a "DNI".
-Add another integer that we are going to use to store the Rewards for every quest. 
-We also will need a pointer Event called <activationEvent> that in the future will be used to create the mission trigger.
The last thing we are going to need is a list of Events called <subMissions> we are going to use it to store subevents. 
(Quests are groups of submissions or "subquests/events")
*/

class Quest
{
public:
	Quest() {};
	~Quest();
	
	int DNI; 
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
/*TODO 3: Here we have the xmlfile and the three list i talk you few minutes ago, we will need them in the future*/
	pugi::xml_document xmlfile;

	std::list<Quest*> preparedQuests;    //quest that are not active because the trigger hasn't been triggered
	std::list<Quest*> activatedQuests;   //active quests that you can complete
	std::list<Quest*> endedQuests;       //done quests. You can not use this list and just destroy quests when finished
};
//___________________________________________________




#endif
