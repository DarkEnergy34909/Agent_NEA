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

std::pair<int, int> Enemy::calculatePath(int x, int y, int levelGrid[6][8]) {
	// Initialise a queue to store positions on the grid to visit
	std::queue<GridPosition> positionQueue;

	// Initialise a map to store visited positions and their previous positions
	std::unordered_map<GridPosition, GridPosition> visited;

	// Calculate starting position on the grid
	int startingPosX = (this->posX / 640) * 8; // TODO: Replace these values with constants 
	int startingPosY = (this->posY / 480) * 6;

	GridPosition startingPosition = { startingPosX, startingPosY };

	// Add the starting position to the queue 
	positionQueue.push(startingPosition);

	// Add the starting position to the visited map with a dummy value (represents no previous position)
	visited[startingPosition] = { -1, -1 };

	// Calculate the target position
	int targetPosX = (x / 640) * 8;
	int targetPosY = (y / 480) * 6;

	GridPosition targetPosition = { targetPosX, targetPosY };

	// Initialise current position in the grid
	GridPosition currentPosition = startingPosition;

	// While the target position has not been reached
	while (currentPosition.x != targetPosition.x && currentPosition.y != targetPosition.y) {

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
	while ((visited[currentPosition].x != startingPosition.x && visited[currentPosition].y != startingPosition.y) || (visited[currentPosition].x != -1 && visited[currentPosition].y != -1)) {
		// Set the current position to the previous position in the path
		currentPosition = visited[currentPosition];
	}

	// Calculate the actual x and y position of the next position in the path
	int nextX = (currentPosition.x / 8) * 640;
	int nextY = (currentPosition.y / 6) * 480;

	// Return the next position in the path
	return { nextX, nextY };




}

std::vector<GridPosition> Enemy::getAdjacentPositions(GridPosition position, int levelGrid[6][8]) {
	// Initialise vector to store adjacent positions
	std::vector<GridPosition> adjacentPositions;

	// Get the node to the left of the current node if it is within the grid
	if (position.x != 0) {
		GridPosition left = { position.x - 1, position.y };

		// If the node is not a wall, add it to the vector
		if (levelGrid[left.y][left.x] == 0) {
			adjacentPositions.push_back(left);
		}
	}

	// Get the node to the right of the current node if it is within the grid
	if (position.x != 7) {
		GridPosition right = { position.x + 1, position.y };

		// If the node is not a wall, add it to the vector
		if (levelGrid[right.y][right.x] == 0) {
			adjacentPositions.push_back(right);
		}
	}

	// Get the node above the current node if it is within the grid
	if (position.y != 0) {
		GridPosition up = { position.x, position.y - 1 };

		// If the node is not a wall, add it to the vector
		if (levelGrid[up.y][up.x] == 0) {
			adjacentPositions.push_back(up);
		}
	}

	// Get the node below the current node if it is within the grid
	if (position.y != 5) {
		GridPosition down = { position.x, position.y + 1 };

		// If the node is not a wall, add it to the vector
		if (levelGrid[down.y][down.x] == 0) {
			adjacentPositions.push_back(down);
		}
	}

	// Return the vector of adjacent positions
	return adjacentPositions;
}
