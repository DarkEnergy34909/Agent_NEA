#pragma once
#include "Character.h"

enum Awareness {
	PASSIVE,
	ALERTED
};

enum EnemyType {
	BASIC
};

class Enemy : public Character {
	public:
		// Constructor
		Enemy(Texture* texture, int posX, int posY, int width, int height, int enemyType);

		// Destructor
		~Enemy();

		// Moves the enemy towards a given point
		void moveTo(int x, int y);

		// Calculates a path to a point and returns the next point in the path
		std::pair<int, int> calculatePath(int x, int y, int levelGrid[4][4]);

		// Detects whether a point is within the enemy's cone of vision
		bool pointInVision(int x, int y);

		// Renders the enemy and its vision cone
		void render() override;
	private:
		// The distance at which the enemy can see the player
		int visionRadius;

		// The angle of the enemy's vision cone 
		double visionAngle;

		// The awareness level of the enemy
		int awareness;

};