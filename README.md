## Introduction to quest management
So I needed to create a system to manage events that could be easily implemented in our games throw an XML file and be able to be activated and deactivated when finished. I had worked with other management systems before but this research work was going to be different. I had never worked with real missions in a game and if there was a mission it was very primitive and hardcoded. So it was time to try a new Quest manager!
I prepared this guide to be a easy tutorial to follow but if you have any doubs contact me on: jaumavi1999@hotmail.com

## DOWNLOAD LINKS
Quest_Manager code and exercices:
[Quest Manager Exercices and code solution]()
Executable version:
[Quest Manager fully working version]()

### How does a quest manager works?
If we want to create a fully new quest manager we will need to start by the quests designs. That means to ask ourselves what kind of states, rewards or types our quests will have. We should think about how to know when a quest is finished and how are we going to write all this information in a xml file. When I asked myself about all this things, I end up creating the following structure:

 - Quests: Quests will be composed by events, activation events and other events with other optional functionalities . Quests will be    stored in different lists, each list will contain quests with different states, quests that haven’t been activated will be in the “preparedQuests” list. Activated quest in “activatedQuests” list and finished quests in the “endedQuests” list.

 - Events: Each event will have a type which will mean each event will have a diferent submission inside. In my code I implemented a “TOUCH_EVENT” which means you need to touch an object to pass the event. As I said, every quest have events inside. Once every event has been completed, the current quest will be finished. Events also can be normal submissions that when they are completed the mission ends or activation events which means that even if the quest hasn't been started, if you trigger that event, this will start its mission.

Code should look something like this for Quests and Events structure:

Quest:

![Quest Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Quest.png?raw=true)

Event:

![Event Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Event.png?raw=true)

So you maybe are asking yourself… Who handles all this quests, events and information and make it work together? 
A quest Manager!

## The Quest Manager

You may be worried about what you are going to read in the next few lines but it is easier than it seems. All the work is here, in these 
three lists:

![Quest_Manager Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Quest_Manager.png?raw=true)

The manager is the one that will handle quests and decide where they should go. Prepared quests are the ones that have been stored and prepared to be activated by the activation event. These quests can go to the second list if we trigger the activation event. If a quest is finished will end up in the ended quests list.

### Do you really understand What are events?

We call an event to something that happens and it was prepared previously to happen in an specific way. For example: if we touch an object in our game and the object suddenly gives us gold.
This is a very simple event and if we take this object and we hide it, we have a new mission called: “find the treasure”. If we want the player to notice that his mission is to find the treasure we will need an activation event that can be something like a pnj that talks with you and ask you to find his treasure and give you a part of ir.
So in every quest there are two types of events, the ones that start the mission and the ones that must be completed to complete the quest and receive the reward. If you want to activate a quest talking with an npc you will need to add a “Talk with x npc” event and add it the activator characteristic to activate the npc quest. This event could not be used to activate a quest but to finish a quest.
Once a mission has been activated, when all events are done the mission ends giving you a reward and being moved to “ended quests” list.
Specific types of events like the example above will be needed to create different style events.

![Touch_Event Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Touch_Event.png?raw=true)

### How do we create new quests using an xml file?

I think the most useful way to explain this is to show you the xml file.

![XML_File](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/XML_File.png?raw=true)

















