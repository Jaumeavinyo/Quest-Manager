#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "Module.h"
#include "Entity.h"
#include "PugiXml\src\pugixml.hpp"

#define TIMES_PER_SEC 5

class EntityManager : public Module
{
public:

	EntityManager();
	~EntityManager();

public:

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

public:

	Entity *CreateEntity(entity_type entityType);
	void DestroyEntity(Entity *Entity);

public:

	std::list<Entity*> entities_list;

	float accumulated_time = 0.0f;
	float update_ms_cycle = 0.0f;
	int times_per_sec = 0;
	bool do_logic = false;

};

#endif