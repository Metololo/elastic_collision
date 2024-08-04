#include <SFML/Graphics.hpp>
#include "includes/Particle.hpp"

Particle::Particle(float radius, sf::Vector2f position, sf::Vector2f velocity)
{
	this->circle.setRadius(radius);
	this->circle.setPosition(position);

	sf::Color darkBlue(59, 89, 152, 255);
	sf::Color blue(108, 52, 131, 255);
	sf::Color lightBlue(247, 247, 247, 255);

	int r = rand() % 3;

	if (r == 0)
	{
		this->circle.setFillColor(darkBlue);
	}
	else if (r == 1)
	{
		this->circle.setFillColor(blue);
	}
	else
	{
		this->circle.setFillColor(lightBlue);
	}

	this->setVelocity(velocity);
	this->mass = (float)M_PI * radius * radius;
}

sf::Vector2f Particle::getPosition()
{
	return this->circle.getPosition();
}

sf::Vector2f Particle::getVelocity()
{
	return this->velocity;
}

float Particle::getRadius()
{
	return this->circle.getRadius();
}

void Particle::setCenter(sf::Vector2f center)
{
	float radius = this->getRadius();
	this->circle.setPosition(sf::Vector2f(center.x - radius, center.y - radius));
}

void Particle::setPosition(sf::Vector2f position)
{
	this->circle.setPosition(position);
}

sf::Vector2f Particle::getCenter()
{
	float x = this->circle.getPosition().x + this->getRadius();
	float y = this->circle.getPosition().y + this->getRadius();

	return sf::Vector2f(x, y);
}

float Particle::getMass()
{
	return this->mass;
}

void Particle::setVelocity(const sf::Vector2f velocity)
{
	this->velocity.x = velocity.x;
	this->velocity.y = velocity.y;
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(circle);
}

void Particle::update(float dt, sf::RenderWindow &window)
{
	float c_x = circle.getPosition().x;
	float c_y = circle.getPosition().y;

	circle.setPosition(sf::Vector2f(dt * velocity.x + c_x, dt * velocity.y + c_y));

	float left = circle.getPosition().x;
	float right = circle.getPosition().x + circle.getRadius() * 2;
	float top = circle.getPosition().y;
	float bottom = circle.getPosition().y + circle.getRadius() * 2;

	if (left <= 0)
	{
		velocity.x = -velocity.x;
		circle.setPosition(0, circle.getPosition().y);
	}

	if (right >= window.getSize().x)
	{
		velocity.x = -velocity.x;
		circle.setPosition(window.getSize().x - circle.getRadius() * 2, circle.getPosition().y);
	}

	if (top <= 0)
	{
		velocity.y = -velocity.y;
		circle.setPosition(circle.getPosition().x, 0);
	}

	if (bottom >= window.getSize().y)
	{
		velocity.y = -velocity.y;
		circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius() * 2);
	}
}
