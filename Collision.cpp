#include "includes/Collision.hpp"

float Collision::distanceBetween(sf::Vector2f d1, sf::Vector2f d2)
{
	sf::Vector2f deltaPos = d2 - d1;
	return std::sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
}

void Collision::separateParticles(Particle &particle1, Particle &particle2)
{
	sf::Vector2f p1 = particle1.getCenter();
	sf::Vector2f p2 = particle2.getCenter();
	sf::Vector2f v1 = particle1.getVelocity();
	sf::Vector2f v2 = particle2.getVelocity();

	float distance = sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	float overlap = 0.5f * (distance - particle1.getRadius() - particle2.getRadius());

	particle1.setCenter(sf::Vector2f(p1.x - (overlap * (p1.x - p2.x) / distance), p1.y - (overlap * (p1.y - p2.y) / distance)));
	particle2.setCenter(sf::Vector2f(p2.x - (overlap * (p2.x - p1.x) / distance), p2.y - (overlap * (p2.y - p1.y) / distance)));
}

void Collision::handleParticleCollision(Particle &particle1, Particle &particle2)
{
	float radius1 = particle1.getRadius();
	float radius2 = particle2.getRadius();

	if (distanceBetween(particle1.getCenter(), particle2.getCenter()) >= radius1 + radius2)
	{
		return;
	}

	separateParticles(particle1, particle2);

	sf::Vector2f p1 = particle1.getPosition();
	sf::Vector2f p2 = particle2.getPosition();
	sf::Vector2f velocity1 = particle1.getVelocity();
	sf::Vector2f velocity2 = particle2.getVelocity();
	sf::Vector2f deltaVelocity = velocity2 - velocity1;
	sf::Vector2f deltaPosition = particle2.getPosition() - particle1.getPosition();

	float m1 = particle1.getMass();
	float m2 = particle2.getMass();

	velocity2 -= (2 * m1 / (m2 + m1)) * (float)(((deltaVelocity.x * deltaPosition.x) + (deltaVelocity.y * deltaPosition.y)) / (pow((deltaPosition.x), 2) + pow((deltaPosition.y), 2))) * deltaPosition;
	deltaPosition = (-deltaPosition);
	deltaVelocity = (-deltaVelocity);
	velocity1 -= (2 * m2 / (m1 + m2)) * (float)(((deltaVelocity.x * deltaPosition.x) + (deltaVelocity.y * deltaPosition.y)) / (pow((deltaPosition.x), 2) + pow((deltaPosition.y), 2))) * deltaPosition;

	particle1.setVelocity(velocity1);
	particle2.setVelocity(velocity2);
}
