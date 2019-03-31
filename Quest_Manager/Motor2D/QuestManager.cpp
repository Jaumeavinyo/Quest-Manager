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
	/*TODO 4:
	-We need to read an xml file so we could start looking what is inside the xmlfile: <Quest_Manager\Game\questData.xml>
	-store inside a xml_node the necessary info to read our file, you can use the function: <LoadQuestsXML(xmlfile,"path") - inside "myApp";> 
	*/
	pugi::xml_node xmlReader;
	xmlReader = myApp->LoadQuestsXML(xmlfile,"questData.xml");  //Loads the xml file that you pass in the "xmlfile" and returns a node

	if (xmlReader == NULL) {
		LOG("Could not load questsfile.xml into xmlReader");
	}else /*TODO 5: 
		  -Lets read the xml and store the data in a new Quest. (Note that we can have more than one quest :D)
		  -If you need a hint you can search <Hint 1>
		  */
		for (xmlReader = xmlReader.child("quest"); xmlReader; xmlReader = xmlReader.next_sibling("quest")) {
			Quest* newQuest = new Quest();
			newQuest->DNI = xmlReader.attribute("DNI").as_int();
			newQuest->Reward = xmlReader.attribute("Reward").as_int();
			/*TODO 6:
			-As you have seen in the xml file, inside a quest we have 2 types of submissions ("ActivationEvent" and "SubEvent");
			The activation event will activate the quest so it can be completed. 
			-To do this we are going to acces the type_Event* "activationEvent" of the quest class created in the tod0 1 and asign it some info.
			You will use the the function <createEvent()> that (ofcourse you will need to code later hehe) to create an activationevent with the necessary info.			
			*/
			newQuest->activationEvent = createEvent(xmlReader.child("ActivationEvent"));


			/*TODO 8:
			-Okey, now that we created the createEvent function we are going to store all submissions and their info in a list called <subMissions> 
			that you can find in the header
			-Yes, this is about creating another for to read all submissions/subevents info and store them in new events that you will create with the function
			<createEvent()>
			-I almost forgot to tell you that you also will need to store the submissions into the submission list.
			For a hint search <Hint 2>
			*/
			pugi::xml_node subMissionsReader;
			for (subMissionsReader = xmlReader.child("SubEvent"); subMissionsReader; subMissionsReader = subMissionsReader.next_sibling("SubEvent")) {
				newQuest->subMissions.push_back(createEvent(subMissionsReader));
			}
			/*TODO 9:
			-There is just 1 more line to code here: you should add the newquest to the list <preparedQuests> 
			(this means this quest will be sleeping until we touch the trigger/activation envent)
			*/
			preparedQuests.push_back(newQuest);
		}



	
	
	return ret;
}
Event* Quest_Manager::createEvent(pugi::xml_node &xmlReader) {
	/*xmlReader = xmlReader.child("ActivationEvent");*/
	/*TODO 7:
	-Okey, you already know how this works, but you will need to check which type of event we are going to create. For the moment there is only one type (1) of event
	but I spect you to create more types in your own games so we need a "type" selector. if type is 1 we are going to create a <TouchEvent> if type is 2 in your games 
	you will create a: MonsterEvent (for example)

	*/
	int Type = xmlReader.attribute("Type").as_int();

	if(Type == 1){
		TouchEvent* ret = new TouchEvent();

		ret->Object.x = xmlReader.child("Object").attribute("x").as_int();
		ret->Object.y = xmlReader.child("Object").attribute("y").as_int();
		ret->Object.w = xmlReader.child("Object").attribute("w").as_int();
		ret->Object.h = xmlReader.child("Object").attribute("h").as_int();
		
		return ret;
	}
}
