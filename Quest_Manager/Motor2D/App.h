#ifndef APP_H
#define APP_H

#include "Module.h"
#include "PugiXml\src\pugixml.hpp"

#include "Timer.h"
#include <list>

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class PathFinding;
class EntityManager;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	Window*			win = NULL;
	Input*			input = NULL;
	Render*			render = NULL;
	Textures*			tex = NULL;
	Audio*			audio = NULL;
	Scene*			scene = NULL;
	Map*				map = NULL;
	PathFinding*		pathfinding = NULL;
	EntityManager*	entities = NULL;

private:

	int					argc;
	char**				args;

	std::string			title;
	std::string			organization;

	std::list<Module*>modules;


	uint				frame_count = 0;
	Timer				time_since_start;
	Timer				frame_time;
	Timer				last_sec_frame_time;

	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

};

extern App* myApp;

#endif