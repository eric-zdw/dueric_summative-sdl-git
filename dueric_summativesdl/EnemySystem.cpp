#include "EnemySystem.h"
#include "ProjectileSystem.h"

extern int shakeIntensity;

EnemySystem::EnemySystem() {


}

void EnemySystem::SpawnEnemy(SDL_Renderer* renderer)
{
	Enemy newEnemy(renderer);
	enemyList.push_back(newEnemy);
}

void EnemySystem::moveEnemies(ProjectileSystem ps, Player player)
{
	for (int x = 0; x < enemyList.size(); x++)
	{
		enemyList[x].getDirection(player);
		enemyList[x].move();
		for (int y = 0; y < ps.getList().size(); y++)
		{
			if (SDL_HasIntersection(&enemyList[x].getCollisionBox(), &ps.getList()[y].getCollisionBox()) == SDL_TRUE)
			{
				enemyList[x].loseHealth(ps.getList()[y].getDamage());
				ps.getList()[y].setActive(false);
				std::cout << "hit" << std::endl;
				shakeIntensity += 10;
			}
		}
	}
}

void EnemySystem::renderEnemies(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	for (int x = 0; x < enemyList.size(); x++)
	{
		enemyList[x].render(renderer, offsetX, offsetY);
	}
}