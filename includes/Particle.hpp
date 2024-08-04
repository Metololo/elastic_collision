#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <numeric>
#define M_PI 3.14159265358979323846

class Particle : public sf::Drawable
{
private:
	sf::CircleShape circle;
	sf::Vector2f velocity;
	float mass;

public:
	Particle(float radius, sf::Vector2f position, sf::Vector2f velocity);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getRadius();
	void setCenter(sf::Vector2f center);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getCenter();
	float getMass();
	void setVelocity(sf::Vector2f velocity);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void update(float dt, sf::RenderWindow &window);
};
