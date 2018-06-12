#include "../include/renderer.h"

Renderer* Renderer::instance = NULL;

Renderer::Renderer()
{
	LAST = 0;
	deltatime = 0;

	resX = RESOLUTION_X;
	resY = RESOLUTION_Y;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "failed to initialize SDL2: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Could not initiate SDL2_IMG: " << IMG_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}

	if (TTF_Init() == -1) {
		std::cout << "Could not initiate SDL2_TTF: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(-1);
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-2);
	}

	//creates renderer and enables VSYNC
	renderer = SDL_CreateRenderer(window, -1, VSYNC);

	if (renderer == NULL) {
		std::cout << "failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(-3);
	}

	std::cout << "Renderer Created" << std::endl;

	//open font
	font = TTF_OpenFont(FONT, FONT_SIZE);

}

Renderer::Renderer(int rX, int rY)
{
	resX = rX;
	resY = rY;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "failed to initialize SDL2: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	//initialize window
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resX, resY, NULL);

	if (window == NULL)
	{
		std::cout << "failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(-2);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		std::cout << "failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(-3);
	}

	std::cout << "Renderer Created" << std::endl;
}

Renderer::~Renderer()
{
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete window;
	delete renderer;
}

Renderer * Renderer::getInstance()
{
	if (instance == NULL) {
		instance = new Renderer();
	}
	return instance;
}

void Renderer::showTexture(SDL_Texture* tex) {
	SDL_Rect srect;
	srect.x = 0;
	srect.y = 0;
	srect.h = 512;
	srect.w = 512;
	SDL_Rect drect;
	SDL_RenderCopy(renderer, tex, NULL, &srect);
}

void Renderer::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	ShowText();
	SDL_RenderPresent(this->renderer);
	SDL_RenderClear(this->renderer);
	calculateDeltatime();
}

void Renderer::renderEntity(Entity* entity)
{
	bool isSpritesheet = false;
	Texture* texture = NULL;

	//makes difference between texturepath and spritesheet path
	if (entity->texturePath != "" && entity->spitesheetPath == "") {
		texture = GetImage(entity->texturePath);
		isSpritesheet = false;
	}
	else if (entity->texturePath == "" && entity->spitesheetPath != "") {
		texture = GetImage(entity->spitesheetPath);
		isSpritesheet = true;
	}
	else if (entity->texturePath != "" && entity->spitesheetPath != "") {
		std::cout << "ERROR: entity can't have a spritesheet and a texure at the same time" << std::endl;
	}

	if (texture != NULL) {
		SDL_Rect r;
		if (&entity->pos != NULL) {
			r.x = entity->getParentPosition().x;
			r.y = entity->getParentPosition().y;
		}
		if (&entity->size != NULL) {
			r.h = entity->size.y;
			r.w = entity->size.x;
		}
		if (!isSpritesheet) {
			renderTexture(texture, &r, entity->flip, entity);
		}
		else { renderSpritesheet(texture, entity->animator.getChuck(Vector2(entity->animator.playAnimation(entity->animator.animateFromTo.x, &entity->animator.cur, entity->animator.animateFromTo.y), 0), texture->Resolution()), &r, entity->flip, entity); }
	}

	std::vector<std::vector<Entity*>>::iterator it = entity->ZLayers.begin();
	while (it != entity->ZLayers.end())
	{
		std::vector<Entity*>::iterator at = (*it).begin();
		while (at != (*it).end()) {
			renderEntity((*at));
			at++;
		}
		it++;
	}
}

void Renderer::renderScene(Entity * entity)
{
	renderEntity(entity);
}

void Renderer::RenderText(std::string str, SDL_Color c, SDL_Rect *r)
{
	SDL_Surface* surf = TTF_RenderText_Solid(font, str.c_str(), c);

	SDL_Texture* text = SDL_CreateTextureFromSurface(this->renderer, surf);
	textMap.emplace(text, r);
	SDL_FreeSurface(surf);
}

void Renderer::ShowText()
{
	std::map<SDL_Texture*, SDL_Rect*>::iterator it = textMap.begin();
	while (it != textMap.end()) {
		SDL_RenderCopy(this->renderer, (*it).first, NULL, (*it).second);
		SDL_DestroyTexture((*it).first);
		it = textMap.erase(it);
	}
}

void Renderer::renderTexture(Texture* texture, SDL_Rect* rect)
{
	if (texture->tex != NULL) {
		SDL_RenderCopyEx(renderer, texture->tex, NULL, rect, 0, 0, SDL_FLIP_NONE);
	}
}

void Renderer::renderTexture(Texture* texture, SDL_Rect* rect, SDL_RendererFlip flip, Entity* entity)
{
	if (texture->tex != NULL) {
		SDL_RenderCopyEx(renderer, texture->tex, NULL, rect, entity->rot, 0, flip);
	}
}

void Renderer::renderSpritesheet(Texture* texture, SDL_Rect chunk, SDL_Rect* rect) {
	if (texture->tex != NULL) {
		SDL_RenderCopyEx(renderer, texture->tex, &chunk, rect, 0, 0, SDL_FLIP_NONE);
	}
}
void Renderer::renderSpritesheet(Texture* texture, SDL_Rect chunk, SDL_Rect* rect, SDL_RendererFlip flip, Entity* entity) {
	if (texture->tex != NULL) {
		SDL_RenderCopyEx(renderer, texture->tex, &chunk, rect, entity->rot, 0, flip);
	}
}

Texture* Renderer::GetImage(std::string path)
{
	if (path == "")
	{
		return NULL;
	}
	std::map<std::string, Texture*>::iterator it = imageBlob.find(path);
	if (it != imageBlob.end())
	{
		return it->second;
	}
	Texture* t = new Texture(getRenderer(), path);
	imageBlob.emplace(path, t);
	if (t->tex == NULL)
	{
		std::cout << "Image file not found: these are not the images you're looking for" << std::endl;
		delete t;
		return NULL;
	}
	return t;
}

void Renderer::destroyTexture(std::string path)
{
	std::map<std::string, Texture*>::iterator it = imageBlob.find(path);
	if (it != imageBlob.end())
	{
		Texture* texture = imageBlob[path];
		imageBlob.erase(path);
		delete texture;
		return;
	}
	std::cout << "Image not found: its over imagekin, i have the high ground" << std::endl;
}

void Renderer::calculateDeltatime()
{
	Uint64 NOW = SDL_GetTicks();
	deltatime = NOW - LAST;
	deltatime /= 1000;
	LAST = NOW;
}

