#include "Enemy.h"

Enemy::Enemy(Texture* texture, int posX, int posY, int width, int height, int enemyType) : Character(texture, posX, posY, width, height) {
	// Initialise the enemy's awareness - by default, the enemy is passive
	awareness = PASSIVE;

	// Initialise the enemy's type
	this->enemyType = enemyType;
	this->objectType = ENEMY;

	// Initialise vision texture to null initially
	visionTexture = NULL;

	// Initialise the waypoint to a dummy value
	currentWaypoint = { -1, -1 };

	// Initialise the enemy's attributes based on its type
	switch (enemyType) {
		case BASIC:
			// Set the enemy's vision radius
			visionRadius = 150;

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

std::pair<int, int> Enemy::calculatePath(int x, int y, int levelGrid[6][8]) {
	// Initialise a queue to store positions on the grid to visit
	std::queue<GridPosition> positionQueue;

	// Initialise a map to store visited positions and their previous positions
	std::map<GridPosition, GridPosition> visited;

	// Calculate starting position on the grid
	int startingPosX = (this->posX / 640.0) * 8.0; // TODO: Replace these values with constants 
	int startingPosY = (this->posY / 480.0) * 6.0;

	GridPosition startingPosition = { startingPosX, startingPosY };

	// Add the starting position to the queue 
	positionQueue.push(startingPosition);

	// Add the starting position to the visited map with a dummy value (represents no previous position)
	visited[startingPosition] = { -1, -1 };

	// Calculate the target position
	int targetPosX = (x / 640.0) * 8.0;
	int targetPosY = (y / 480.0) * 6.0;

	GridPosition targetPosition = { targetPosX, targetPosY };

	// Initialise current position in the grid
	GridPosition currentPosition = startingPosition;

	// While the target position has not been reached
	while (currentPosition != targetPosition) {

		// If the queue is empty return a dummy value as there is no path to the target
		if (positionQueue.empty()) {
			return { -1, -1 };
		}

		// Get the current position from the queue and remove it from the queue
		currentPosition = positionQueue.front();
		positionQueue.pop();

		// Get the adjacent positions to the current position and add them to the queue if they have not been visited
		std::vector<GridPosition> adjacentPositions = getAdjacentPositions(currentPosition, levelGrid);

		// First check that vector is empty to avoid an error if it is
		if (!adjacentPositions.empty()) {
			for (auto& position : adjacentPositions) {
				
				// Check that position hasn't already been visited
				if (visited.count(position) == 0) {

					// Add position to the queue
					positionQueue.push(position);

					// Add position to the visited map with the current position as the previous position
					visited[position] = currentPosition;
				}
			}
		}
	}

	// If the target position has been reached, backtrack through the visited map and return the next position in the path
	while (visited[currentPosition] != startingPosition && visited[currentPosition] != GridPosition{-1, -1}) {
		// Set the current position to the previous position in the path
		currentPosition = visited[currentPosition];
	}

	// Calculate the actual x and y position of the next position in the path
	int nextX = (currentPosition.first / 8.0) * 640.0;
	int nextY = (currentPosition.second / 6.0) * 480.0;

	// Convert x and y position so the enemy moves to the centre of the tile
	nextX += 80 / 2;
	nextX -= this->width / 2;

	nextY += 80 / 2;
	nextY -= this->height / 2;

	// Return the next position in the path
	return { nextX, nextY };




}

std::vector<GridPosition> Enemy::getAdjacentPositions(GridPosition position, int levelGrid[6][8]) {
	// Initialise vector to store adjacent positions
	std::vector<GridPosition> adjacentPositions;

	// Get the node to the left of the current node if it is within the grid
	if (position.first != 0) {
		GridPosition left = { position.first - 1, position.second };

		// If the node is not a wall, add it to the vector
		if (levelGrid[left.second][left.first] == 0) {
			adjacentPositions.push_back(left);
		}
	}

	// Get the node to the right of the current node if it is within the grid
	if (position.first != 7) {
		GridPosition right = { position.first + 1, position.second };

		// If the node is not a wall, add it to the vector
		if (levelGrid[right.second][right.first] == 0) {
			adjacentPositions.push_back(right);
		}
	}

	// Get the node above the current node if it is within the grid
	if (position.second != 0) {
		GridPosition up = { position.first, position.second - 1 };

		// If the node is not a wall, add it to the vector
		if (levelGrid[up.second][up.first] == 0) {
			adjacentPositions.push_back(up);
		}
	}

	// Get the node below the current node if it is within the grid
	if (position.second != 5) {
		GridPosition down = { position.first, position.second + 1 };

		// If the node is not a wall, add it to the vector
		if (levelGrid[down.second][down.first] == 0) {
			adjacentPositions.push_back(down);
		}
	}

	// Return the vector of adjacent positions
	return adjacentPositions;
}

void Enemy::setAwareness(int awareness) {
	this->awareness = awareness;

	if (awareness == ALERTED) {
		// Set colour of vision texture to red
		if (visionTexture != NULL) {
			visionTexture->setColor(255, 0, 0);
		}
	}
	else if (awareness == PASSIVE) {
		// Set colour of vision texture to white
		if (visionTexture != NULL) {
			visionTexture->setColor(255, 255, 255);
		}
		
	}
}

int Enemy::getAwareness() {
	// Return enemy's awareness level
	return awareness;
}
void Enemy::setWaypoint(std::pair<int, int> waypoint) {
	// Sets the current waypoint
	this->currentWaypoint = waypoint;
}

void Enemy::moveToCurrentWaypoint(int levelGrid[6][8]) {

	std::pair<int, int> nextPos = calculatePath(currentWaypoint.first, currentWaypoint.second, levelGrid);

	moveTo(nextPos.first, nextPos.second);
}

std::pair<int, int> Enemy::getCurrentWaypoint() {
	// Returns the current waypoint
	return currentWaypoint;
}

void Enemy::render() {
	// First render the vision circle (under the character)
	if (visionTexture != NULL) {
		// Render the vision texture (to the centre of the enemy)
		visionTexture->render(posX + (width / 2) - visionRadius, posY + (height / 2) - visionRadius);
	}

	// Copied from Character::render()
	// If not moving , render the entity normally
	if ((velX == 0 && velY == 0) || animationTextures.empty()) {
		texture->render(posX, posY);

		// Reset the animation
		currentFrame = 0;
	}
	else {
		// Render the Entity with the current animation texture
		animationTextures[currentFrame]->render(posX, posY);

		// Increment frame delay counter
		frameDelayCounter++;

		// If frame delay is reached, increment the current frame
		if (frameDelayCounter == frameDelay) {
			// Reset frame delay
			frameDelayCounter = 0;

			// Move onto the next texture
			currentFrame++;
		}

		// If the end of the animation is reached, reset the animation
		if (currentFrame == animationTextures.size()) {
			currentFrame = 0;
		}
	}

	// Render the weapon if the character has one
	if (weapon != NULL) {
		switch (weapon->getWeaponType()) {
		case PISTOL:
			// Check the angle of the weapon
			// If the weapon is pointed to the right, render the gun to the right of the character
			if (weapon->getAngle() > -90.0 && weapon->getAngle() < 90.0) {
				weapon->render(posX + (3 * width / 4), posY + (height / 2));
			}
			// If the weapon is pointed to the left, render the gun to the left of the character
			else {
				weapon->render(posX + (width / 4) - weapon->getTexture()->getWidth(), posY + (height / 2));
			}
			break;
		default:
			// If the weapon type is invalid, print an error message
			std::cout << "Invalid weapon type" << std::endl;
			break;
		}
	}
}

void Enemy::setVisionTexture(Texture* texture) {
	// Set the vision texture
	this->visionTexture = texture;

	// Set the width and height of the vision texture
	visionTexture->setWidth(visionRadius * 2);
	visionTexture->setHeight(visionRadius * 2);
}

int Enemy::getVisionRadius() {
	// Return the vision radius
	return visionRadius;
}

bool Enemy::canSee(SDL_Rect collider) {
	// Check if the centre of the collider is within the vision circle

	// Calculate the centre of the collider
	int colliderCentreX = collider.x + (collider.w / 2);
	int colliderCentreY = collider.y + (collider.h / 2);

	// Calculate the centre of the vision circle
	int visionCentreX = posX + (width / 2);
	int visionCentreY = posY + (height / 2);

	// Calculate the distance between the two centres using Pythagoras
	int distance = sqrt(pow(visionCentreX - colliderCentreX, 2) + pow(visionCentreY - colliderCentreY, 2));

	return distance < visionRadius;
}
