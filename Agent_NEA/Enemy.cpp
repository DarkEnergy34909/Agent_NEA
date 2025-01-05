#include "Enemy.h"

Enemy::Enemy(Texture* texture, int posX, int posY, int width, int height, int enemyType) : Character(texture, posX, posY, width, height) {
	// Initialise the enemy's awareness - by default, the enemy is passive
	awareness = PASSIVE;

	// Initialise the enemy's type
	this->enemyType = enemyType;

	// Initialise the enemy's attributes based on its type
	switch (enemyType) {
		case BASIC:
			// Set the enemy's vision radius
			visionRadius = 100;

			// Set the enemy's vision angle
			visionAngle = 45;

			break;
		default:
			// If the enemy type is invalid, print an error message
			std::cout << "Invalid enemy type" << std::endl;

			// Initialise attrributes to default values
			visionRadius = 0;
			visionAngle = 0;

			break;
	}
}

Enemy::~Enemy() {
	// Do nothing
}

void Enemy::moveTo(int x, int y) {
	// If the enemy's x position is less than the target x position, move the enemy right
	if (this->posX < x) {
		this->velX = this->velMax;
	}
	// If the enemy's x position is greater than the target x position, move the enemy left
	else if (this->posX > x) {
		this->velX = -(this->velMax);
	}
	// If the enemy's x position is equal to the target x position, stop moving in the x-direction
	else {
		this->velX = 0;
	}

	// If the enemy's y position is less than the target y position, move the enemy down
	if (this->posY < y) {
		this->velY = this->velMax;
	}
	// If the enemy's y position is greater than the target y position, move the enemy up
	else if (this->posY > y) {
		this->velY = -(this->velMax);
	}
	// If the enemy's y position is equal to the target y position, stop moving in the y-direction
	else {
		this->velY = 0;
	}
}

/*std::pair<int, int> Enemy::calculatePath(int x, int y, int levelGrid[6][8]) {

}*/

