#include <SFML/Graphics.hpp>
#include <iostream>
#include "includes/Particle.hpp"
#include "includes/Collision.hpp"


sf::Vector2f getRandomParticlePosition(sf::RenderWindow& window, float radius);
sf::Vector2f getRandomParticleVelocity();


int main()
{
	srand(time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "My window test", sf::Style::Default, settings);

	const int fps = 60;
	window.setFramerateLimit(fps);
	window.setVerticalSyncEnabled(true);

	sf::Font font;
	font.loadFromFile("assets/fonts/OpenSans.ttf");

	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setPosition(10, 10);
	fpsText.setString("Text");
	fpsText.setCharacterSize(16);
	fpsText.setFillColor(sf::Color::White);

	const float velMultiplier = 100.f;

	std::vector<Particle*> particles;

	for (int i = 0; i < 100; ++i) {
		float radius = 10;
		sf::Vector2f position = getRandomParticlePosition(window, radius);
		sf::Vector2f velocity = getRandomParticleVelocity();
		particles.push_back(new Particle(radius, position, velocity * velMultiplier));
	}

	float dt = 0;
	float lastTime = 0.f;

	sf::Clock clock;

	while (window.isOpen()) {

		window.clear();

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		float dt = clock.restart().asSeconds();
		lastTime += dt;

		if (lastTime >= 0.05f) {
			float fps = 1.f / (dt);
			fpsText.setString(std::to_string(fps) + " fps    particles : " + std::to_string(particles.size()));
			lastTime = 0;
		}

		// could be optimized with kd-tree in the future
		for (int i = 0; i < particles.size(); ++i) {
			for (int j = i+1; j < particles.size(); ++j) {
				Collision::handleParticleCollision(*particles[i], *particles[j]);
			}
		}

		for (auto particle : particles) {
			particle->update(dt, window);
			window.draw(*particle);
		}

		window.draw(fpsText);


		window.display();
	}

	return 0;

}

sf::Vector2f getRandomParticlePosition(sf::RenderWindow& window, float radius) {
	float randomX = rand() % (int)(window.getSize().x - radius * 2);
	float randomY = rand() % (int)(window.getSize().y - radius * 2);
	return sf::Vector2f(randomX, randomY);
}

sf::Vector2f getRandomParticleVelocity() {
	float vx = rand() % 2 - 0.8f;
	float vy = rand() % 2 - 0.8f;
	return sf::Vector2f(vx, vy);
}