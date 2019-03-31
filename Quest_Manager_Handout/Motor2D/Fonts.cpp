#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

Fonts::Fonts() : Module()
{}

// Destructor
Fonts::~Fonts()
{}

// Called before render is available
bool Fonts::Awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");
	bool ret = true;

	if (TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	else
	{
		const char* path = conf.child("defaultFont").attribute("file").as_string(DEFAULT_FONT);
		int size = conf.child("defaultFont").attribute("size").as_int(DEFAULT_FONT_SIZE);
		defaultFont = Load(path, size);
	}

	return ret;
}

// Called before quitting
bool Fonts::CleanUp()
{
	LOG("Freeing True Type fonts and library");

	for (std::list<_TTF_Font*>::iterator iter = fonts.begin(); iter != fonts.end(); ++iter) {
		TTF_CloseFont(*iter);
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
TTF_Font* const Fonts::Load(const char* path, int size)
{
	TTF_Font* font = TTF_OpenFont(path, size);

	if (font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
	}
	else
	{
		LOG("Successfully loaded font %s size %d", path, size);
		fonts.push_front(font);
	}

	return font;
}

// Print text using font
SDL_Texture* Fonts::Print(const char* text, SDL_Color color, _TTF_Font* font)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface = TTF_RenderText_Blended((font) ? font : defaultFont, text, color);

	if (surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		ret = myApp->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}

// calculate size of a text
bool Fonts::CalcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	bool ret = false;

	if (TTF_SizeText((font) ? font : defaultFont, text, &width, &height) != 0)
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
		ret = true;

	return ret;
}