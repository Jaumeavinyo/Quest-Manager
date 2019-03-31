#include "QuestManager.h"
#include "Module.h"
#include "Point.h"
#include "Log.h"
#include <vector>
#include "App.h"


Quest_Manager::Quest_Manager() {
}
Quest_Manager::~Quest_Manager() {

	for (std::list <Quest*>::iterator it = preparedQuests.begin(); it != preparedQuests.end(); it++) {
		preparedQuests.erase(it);
	}
		

	for (std::list <Quest*>::iterator it = activatedQuests.begin(); it != activatedQuests.end(); it++) {
		activatedQuests.erase(it);
	}
		

	for (std::list <Quest*>::iterator it = endedQuests.begin(); it != endedQuests.end(); it++) {
		endedQuests.erase(it);
	}
		
}
bool Quest_Manager::Awake(pugi::xml_node& config) {
	LOG("STARTING QUESTMANAGER");
	return true;
}
bool Quest_Manager::Start() {

	bool ret = true;

	pugi::xml_node xmlReader;
	xmlReader = myApp->LoadQuestsXML(xmlfile,"questData.xml");  //Loads the xml file that you pass in the "xmlfile" and returns a node

	if (xmlReader == NULL) {
		LOG("Could not load questsfile.xml into xmlReader");
	}else
		for (xmlReader = xmlReader.child("quest"); xmlReader; xmlReader = xmlReader.next_sibling("quest")) {
			Quest* newQuest = new Quest();
			newQuest->DNI = xmlReader.attribute("DNI").as_int();
			newQuest->Reward = xmlReader.attribute("Reward").as_int();

			newQuest->activationEvent = createEvent(xmlReader.child("ActivationEvent"));

			pugi::xml_node subMissionsReader;
			for (subMissionsReader = xmlReader.child("SubEvent"); subMissionsReader; subMissionsReader = subMissionsReader.next_sibling("SubEvent")) {
				newQuest->subMissions.push_back(createEvent(subMissionsReader));
			}

			preparedQuests.push_back(newQuest);
		}



	
	
	return ret;
}
Event* Quest_Manager::createEvent(pugi::xml_node &xmlReader) {
	/*xmlReader = xmlReader.child("ActivationEvent");*/
	int Type = xmlReader.attribute("Type").as_int();

	if(Type == 1){
		MovementEvent* ret = new MovementEvent();

		ret->Object.x = xmlReader.child("ObjectOnCamera").attribute("x").as_int();
		ret->Object.y = xmlReader.child("ObjectOnCamera").attribute("y").as_int();
		ret->Object.w = xmlReader.child("ObjectOnCamera").attribute("w").as_int();
		ret->Object.h = xmlReader.child("ObjectOnCamera").attribute("h").as_int();
		
		return ret;
	}
}

