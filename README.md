## Introduction to quest management
So I needed to create a system to manage events that could be easily implemented in our games throw an XML file and be able to be activated and deactivated when finished. I had worked with other management systems before but this research work was going to be different. I had never worked with real missions in a game and if there was a mission it was very primitive and hardcoded. So it was time to try a new Quest manager!

## DOWNLOAD LINKS

[Quest Manager Exercices and code solution]()
[Quest Manager fully working version]()

## How does a quest manager works?
If we want to create a fully new quest manager we will need to start by the quests designs. That means to ask ourselves what kind of states, rewards or types our quests will have. We should think about how to know when a quest is finished and how are we going to write all this information in a xml file. When I asked myself about all this things, I end up creating the following structure:

 - Quests: Quests will be composed by events, activation events and other events with other optional functionalities . Quests will be    stored in different lists, each list will contain quests with different states, quests that haven’t been activated will be in the “preparedQuests” list. Activated quest in “activatedQuests” list and finished quests in the “endedQuests” list.

 - Events: Each event will have a type which will mean each event will have a diferent submission inside. In my code I implemented a “TOUCH_EVENT” which means you need to touch an object to pass the event. As I said, every quest have events inside. Once every event has been completed, the current quest will be finished. Events also can be normal submissions that when they are completed the mission ends or activation events which means that even if the quest hasn't been started, if you trigger that event, this will start its mission.

Code should look something like this for Quests and Events structure:

Quest:
![Quest Class](https://github.com/Jaumeavinyo/Quest-Manager/blob/master/ScreenShots/Quest.png)






















You can ue the [editor on GitHub](https://github.com/Jaumeavinyo/Quest-Manager/edit/master/README.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/Jaumeavinyo/Quest-Manager/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
