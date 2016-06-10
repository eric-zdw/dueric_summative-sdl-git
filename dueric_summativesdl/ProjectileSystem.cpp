#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Projectile.h"
#include "PlayerProj.h"

class ProjectileSystem {
private:
	std::vector<PlayerProj> ppList;

public:
	ProjectileSystem(SDL_Renderer*);


	Projectile CreateProjectile();


};