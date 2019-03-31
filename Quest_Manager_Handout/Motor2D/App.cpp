#include <iostream> 
#include <sstream>

#include "Defs.h"
#include "Log.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "Pathfinding.h"
#include "EntityManager.h"
#include "App.h"
#include "QuestManager.h"

#include "Brofiler/Brofiler.h"

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{

	input = new Input();
	win = new Window();
	render = new Render();
	tex = new Textures();
	audio = new Audio();
	scene = new Scene();
	map = new Map();
	pathfinding = new PathFinding();
	//entities = new EntityManager;
	quests = new Quest_Manager();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(scene);
	//AddModule(entities);
	AddModule(quests);

	// render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// release modules
	std::list<Module*>::iterator item = modules.begin();
	
	for (; item != modules.end(); item = next(item))
		RELEASE(*item);

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool App::Awake()
{
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title.assign(app_config.child("title").child_value());
		organization.assign(app_config.child("organization").child_value());
	
		int cap = app_config.attribute("framerate_cap").as_int(-1);

		if (cap > 0)
			capped_ms = 1000 / cap;
	
	}

	if(ret == true)
	{
		std::list<Module*>::iterator item;
		item = modules.begin();

		while(item != modules.end() && ret == true)
		{
			ret = (*item)->Awake(config.child((*item)->name.data())); 
			item = next(item);
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{

	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();

	while (item != modules.end() && ret == true) {

		ret = (*item)->Start();
		item = next(item);
	}

	time_since_start.Start();
	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();



	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;
	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}
pugi::xml_node App::LoadQuestsXML(pugi::xml_document& file,char* path) const
{
	//The xmlfile you pass should be empty, you have one in the questmanager class
	pugi::xml_node ret;
	pugi::xml_parse_result result = file.load_file(path);

	if (result == NULL)
		LOG("Could not load  xml file <loadxmlfunction> pugi error: %s", result.description());
	else
		ret = file.child("quests");

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	//Framerate Calcs
	if (last_sec_frame_time.Read() > 1000) {

		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	//For performance information purposes
	float avg_fps = float(frame_count) / time_since_start.ReadSec();
	float secs_since_start = time_since_start.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	if (capped_ms > 0 && last_frame_ms < capped_ms)
		SDL_Delay(capped_ms - last_frame_ms);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;
	Module* pModule = NULL;
	std::list<Module*>::iterator item = modules.begin();

	for (; item != modules.end() && ret == true; item = next(item)) {

		pModule = (*item);
		if (pModule->active == false)
			continue;

		ret = (*item)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	Module* pModule = NULL;
	std::list<Module*>::iterator item = modules.begin();
	
	for (; item != modules.end() && ret == true; item = next(item)) {

		pModule = *item;
		if (pModule->active == false)
			continue;

		ret = (*item)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	Module* pModule = NULL;
	std::list<Module*>::iterator item = modules.begin();

	for (; item != modules.end() && ret == true; item = next(item)) {

		pModule = *item;
		if (pModule->active == false)
			continue;

		ret = (*item)->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	std::list<Module*>::reverse_iterator item = modules.rbegin();
	
	while (item != modules.rend() && ret == true) {

		ret = (*item)->CleanUp();
		item++;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.data();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.data();
}

// ---------------------------------------
float App::GetDT() const
{
	return dt;
}
