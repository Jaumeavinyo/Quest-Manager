“I am <https://www.linkedin.com/in/jaume-avinyó-b13b17183>(Jaume Avinyó), student of the
<https://www.citm.upc.edu/ing/estudis/graus-videojocs/>(Bachelor’s Degree in
Video Games by UPC at CITM). This content is generated for the second year’s
subject Project 2, under supervision of lecturer
<https://es.linkedin.com/in/ricardpillosu>(Ricard Pillosu).” 


## Introduction to quest management
So I needed to create a system to manage events that could be easily implemented in our games throw an XML file and be able to be activated and deactivated when finished. I had worked with other management systems before but this research work was going to be different. I had never worked with real missions in a game and if there was a mission it was very primitive and hardcoded. So it was time to try a new Quest manager!
I prepared this guide to be a easy tutorial to follow but if you have any doubs contact me on: jaumavi1999@hotmail.com

## DOWNLOAD LINKS
Quest_Manager code and exercices:
[Quest Manager Exercices and code solution]()
Executable version:
[Quest Manager fully working version]()

## How does a quest manager works?
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

## Do you really understand What are events?

We call an event to something that happens and it was prepared previously to happen in an specific way. For example: if we touch an object in our game and the object suddenly gives us gold.
This is a very simple event and if we take this object and we hide it, we have a new mission called: “find the treasure”. If we want the player to notice that his mission is to find the treasure we will need an activation event that can be something like a pnj that talks with you and ask you to find his treasure and give you a part of ir.
So in every quest there are two types of events, the ones that start the mission and the ones that must be completed to complete the quest and receive the reward. If you want to activate a quest talking with an npc you will need to add a “Talk with x npc” event and add it the activator characteristic to activate the npc quest. This event could not be used to activate a quest but to finish a quest.
Once a mission has been activated, when all events are done the mission ends giving you a reward and being moved to “ended quests” list.
Specific types of events like the example above will be needed to create different style events.

![Touch_Event Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Touch_Event.png?raw=true)

## How do we create new quests using an xml file?

I think the most useful way to explain this is to show you the xml file.

![XML_File](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/XML_File.png?raw=true)

As you can see there are two different quests, each quest has a DNI (identification number) and a different reward to give the player when he accomplishes the quest. Every quest need an activation event and this event is “type 1” which means is a touch event. So we know that the activation event is an object that activates the quest if you touch it.
The activation event is not the only event the quest has. Once the quest is activated subEvents turn visible and can be completed. As events are inside a list in the quest class, we can know if all events of a quest are completed to finish the quest.

![SubMissions](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/SubMissions_List.png?raw=true)


## Practical exercice
Lets start with a practical exercice to set up our own quest manager!

TODO 0:
Class Event is already coded but it is very important to know its variables.

TODO 1: Create the class Quest and prepare it to store the elements of the XML_File. Event type will be used to store the activation event and a Event List type will be used to store the rest of variables

![Quest Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Quest.png?raw=true)

TODO 2: Create a enum where you will store your event types. call it: <EVENT_TYPE> and declare a <TOUCH_EVENT>

![enum](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/enum_event_type.png?raw=true)

TODO 3: I just want you to see that we already have 3 preparated lists to start programing with them!

![Lists](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Three%20Lists.png?raw=true)

TODOS 4, 5, 6, 8, 9: We will need to read our XML_File to store its data. We will also need to create events with the function <createEvent()> (this function is coded in TODO 7). Last but not less important will be to store the new quest into the <preparedQuests> List.

![Reader](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/TODOS%204%205%206%208%209.png?raw=true)

TODO 7: We have a function with an XML_Node as an argument and we will read the information to create a new event. We will return a type event.

![createEvent](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/TODO%207.png?raw=true)

TODO 10: The iterator  <it> is a quest and when the activation event is completed we need to move the quest from <preparedQuests> list to <activatedQuests> list.

![Move quests](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/TODO%2010.png?raw=true)

TODO 11: We should think about erasing submissions when complete

![erase submissions](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/TODO%2011.png?raw=true)

TODO 12: Move the quest that is in the iterator <it> to the <endedQuests> list.
 
 ![move](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/TODO%2012.png?raw=true)


##Bibliography

The only usefull webpage I found that helped me with the research was this one

[link](http://www.dannyb.me/posts/2014/02/creating_event_system_c++/)

I also found quite interesting this two videos:

[video_part_1](https://www.youtube.com/watch?v=5mlziHwq90k)
[video_part_2](https://www.youtube.com/watch?v=xnopUoZbMEk&t=624s)

The rest has been done throw deduction and observing other videogames like world of warcraft where missions are very easy to identify.









