#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

class Collision {
private:
	static float distanceBetween(sf::Vector2f d1, sf::Vector2f d2);
	static void separateParticles(Particle& particle1, Particle& particle2);
public:
	Collision() = delete;
	static void handleParticleCollision(Particle& particle1, Particle& particle2);
};
