#include "Weapon.h"

Weapon::Weapon(int weaponType, Texture* texture, Texture* bulletTexture) {
	// Set the weapon type
	this->weaponType = weaponType; 

	// Set the weapon's texture
	this->texture = texture;

	// Set the bullet texture
	this->bulletTexture = bulletTexture;

	// Weapon is not rotated initially
	angle = 0;

	// Load texture and attributes for each weapon type
	switch (weaponType) {
		case PISTOL:
			// Initialise weapon attributes for a pistol
			damage = 20;
			fireDelay = 200;
			ammoCapacity = 12;
			currentAmmo = ammoCapacity;
			reloadTime = 1000;

			break;

		default:
			std::cout << "Invalid weapon type" << std::endl;

			// Set default values
			damage = 0;
			fireDelay = 0;
			ammoCapacity = 0;
			currentAmmo = 0;
			reloadTime = 0;

			break;	
	}
}

Weapon::~Weapon() {
	// Do nothing - do not free the textures as other Weapon instances may be using it
}

void Weapon::render(int posX, int posY) {
	// Calculate the flip of the weapon based on its angle
	SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

	// If the weapon is pointing to the right, do not invert the weapon texture
	if (angle > -90.0 && angle < 90.0) {
		flip = SDL_FLIP_NONE;
	}

	//SDL_Point point = { 0,0 };

	// Render the weapon at the given position with the current angle of the weapon 
	texture->render(posX, posY, NULL, angle, NULL, flip);
}

Bullet* Weapon::fire(int posX, int posY) {
	// If the weapon has ammo, create a bullet and return it
	if (/*currentAmmo > 0*/ true) {
		// Create a new bullet
		Bullet* bullet = new Bullet(bulletTexture, posX, posY, angle, damage);

		// Reduce the current ammo of the weapon by 1
		currentAmmo--;

		// Begin reloading the weapon
		if (currentAmmo == 0) {
			// TODO: Start a timer to reload the weapon
		}

		// Return the bullet
		return bullet;
	}

	else {

		// If the weapon has no ammo, return NULL
		return NULL;
	}
}

int Weapon::getWeaponType() {
	// Return the weapon's type
	return weaponType;
}

int Weapon::getDamage() {
	// Return the damage dealt by the weapon
	return damage;
}

int Weapon::getFireDelay() {
	// Return the delay between shots
	return fireDelay;
}

int Weapon::getAmmoCapacity() {
	// Return the ammo capacity
	return ammoCapacity;
}

int Weapon::getCurrentAmmo() {
	// Return the current ammo
	return currentAmmo;
}

int Weapon::getReloadTime() {
	// Return the reload time
	return reloadTime;
}

void Weapon::setAngle(double angle) {
	// Set the angle of the weapons
	this->angle = angle;
}

double Weapon::getAngle() {
	// Return the angle of the weapon
	return angle;
}
Texture* Weapon::getTexture() {
	// Return the weapon texture
	return texture;
}

Texture* Weapon::getBulletTexture() {
	// Return the bullet texture
	return bulletTexture;
}

