#ifndef SCENE_H
#define SCENE_H
#include "SDL/include/SDL_rect.h"
#include "Module.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//to see if is it inside
	bool isInside(SDL_Rect A,SDL_Rect B);

private:
	SDL_Texture* debug_tex;
	SDL_Rect ValidArea;
	fPoint position;
};

#endif // SCENE_H