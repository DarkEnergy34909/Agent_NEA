#pragma once
#include "Texture.h"
#include "Bullet.h"

// Weapon types
enum WeaponType {
	PISTOL
};

class Weapon {
	public:
		Weapon(int weaponType, Texture* texture, Texture* bulletTexture);

		~Weapon();

		// Renders the weapon - x and y are needed because the weapon is rendered relative to the player, angle is needed for rotation
		void render(int posX, int posY);

		// Fires the weapon - returns a bullet
		Bullet* fire(int posX, int posY);

		// Getters
		int getWeaponType();

		int getDamage();

		int getFireDelay();

		int getAmmoCapacity();

		int getCurrentAmmo();

		int getReloadTime();

		double getAngle();

		Texture* getTexture();

		Texture* getBulletTexture();

		// Setters

		// Set the angle of the weapon
		void setAngle(double angle);
		
	private:
		// The texture of the weapon
		Texture* texture;

		// The texture of the bullets fired by the weapon
		Texture* bulletTexture;

		// The type of the weapon
		int weaponType;

		// The angle the weapon is rotated by
		double angle;

		// Weapon attributes

		// The damage dealt by the weapon
		int damage;

		// The delay between shots (in millseconds)
		int fireDelay;

		// Number of bullets in each magazine
		int ammoCapacity;

		// Current ammo
		int currentAmmo;

		// Time taken for the weapon to reload (in millseconds)
		int reloadTime;
};