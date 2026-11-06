#pragma once

#include "engine/game_system.hpp"
#include <box2d/box2d.h>
#include "engine/renderer.hpp"
#include <SFML/Graphics.hpp>



class PhysicsScene : public Scene {
private:
	b2WorldId world_id; //an id to the physic world
	std::vector<b2BodyId> bodies;
	std::vector<std::shared_ptr<sf::RectangleShape>> sprites;
public:
	PhysicsScene() = default;
	void update(const float& dt) override;
	void render() override;
	void load() override;
	void unload() override;

};

struct Scenes {
	static std::shared_ptr<Scene> physics;
};