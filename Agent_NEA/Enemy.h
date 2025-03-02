#pragma once
#include "Character.h"
#include "Constants.h"
#include <queue>
#include <map>

enum Awareness {
	PASSIVE,
	ALERTED
};

enum EnemyType {
	BASIC
};

typedef std::pair<int, int> GridPosition;

class Enemy : public Character {
	public:
		// Constructor
		Enemy(Texture* texture, int posX, int posY, int width, int height, int enemyType);

		// Destructor
		~Enemy();

		// Moves the enemy towards a given point
		void moveTo(int x, int y);

		// Calculates a path to a point and returns the next point in the path
		std::pair<int, int> calculatePath(int x, int y, int levelGrid[VERTICAL_TILES][HORIZONTAL_TILES]);

		// Detects whether an object is within the enemy's cone of vision
		bool canSee(SDL_Rect collider);

		// Sets the awareness level of the enemy
		void setAwareness(int awareness);

		// Renders the enemy and its vision cone
		void render(int camX = 0, int camY = 0) override;

		// Renders the enemy's vision cone
		void renderVision(int camX = 0, int camY = 0);

		// Returns the awareness level of the enemy
		int getAwareness();

		// Moves the enemy to a waypoint
		void moveToCurrentWaypoint(int levelGrid[VERTICAL_TILES][HORIZONTAL_TILES]);

		// Sets the waypoint
		void setWaypoint(std::pair<int, int> waypoint);

		// Returns the current waypoint
		std::pair<int, int> getCurrentWaypoint();

		// Sets the enemy's vision texture
		void setVisionTexture(Texture* texture);

		// Returns the enemy's vision radius
		int getVisionRadius();

	private:
		// The distance at which the enemy can see the player
		int visionRadius;

		// The angle of the enemy's vision cone 
		double visionAngle;

		// The awareness level of the enemy
		int awareness;

		// The type of enemy
		int enemyType;

		// Gets adjacent grid positions
		std::vector<GridPosition> getAdjacentPositions(GridPosition position, int levelGrid[VERTICAL_TILES][HORIZONTAL_TILES]);

		// Calculates the Manhattan distance between grid positions (for a heuristic)	
		int heuristic(GridPosition a, GridPosition b);

		// The current waypoint the enemy is moving towards
		std::pair<int, int> currentWaypoint;

		// The enemy's vision texture
		Texture* visionTexture;
};

