#include "game_parameters.hpp"
#include "scenes.hpp"
#include "b2d_utils.hpp"

namespace b2 = box2d;

namespace param = Parameters;


void PhysicsScene::load() {
    b2WorldDef world_def = b2DefaultWorldDef();

    world_def.gravity = b2Vec2({ 0.0f, param::g });

    world_id = b2CreateWorld(&world_def);

    for (int i = 1; i < 11; ++i) {
        // Create SFML shapes for each box
        std::shared_ptr<sf::RectangleShape> s = std::make_shared<sf::RectangleShape>();
        s->setPosition(sf::Vector2f(i * (param::game_width / 12.f), param::game_height * .7f));
        s->setSize(sf::Vector2f(50.0f, 50.0f));
        s->setOrigin(sf::Vector2f(25.0f, 25.0f));
        s->setFillColor(sf::Color::White);
        sprites.push_back(s);

        // Create a dynamic physics body for the box
        b2BodyId b = b2::create_physics_box(world_id, true, s);
        // Give the box a spin
        b2Body_ApplyAngularImpulse(b, 5.0f, true);
        bodies.push_back(b);
    }

    sf::Vector2f walls[] = {
        // Top
        sf::Vector2f(param::game_width * .5f, 5.f),
        sf::Vector2f(param::game_width, 10.f),

        // Bottom
        sf::Vector2f(param::game_width * .5f, param::game_height - 5.f),
        sf::Vector2f(param::game_width, 10.f),

        // Left
        sf::Vector2f(5.f, param::game_height * .5f),
        sf::Vector2f(10.f, param::game_height),

        // Right
        sf::Vector2f(param::game_width - 5.f, param::game_height * .5f),
        sf::Vector2f(10.f, param::game_height)
    };

    for (int i = 0; i < 7; i += 2) {
        // Create an SFML rectangle for this wall
        auto s = std::make_shared<sf::RectangleShape>();

        s->setPosition(walls[i]);
        s->setSize(walls[i + 1]);

        // Centre the rectangle's origin
        s->setOrigin(walls[i + 1] * 0.5f);

        s->setFillColor(sf::Color::White);

        // Store the SFML rectangle
        sprites.push_back(s);

        // Create a STATIC Box2D body
        b2BodyId b = box2d::create_physics_box(world_id, false, s);

        // Store its physics ID
        bodies.push_back(b);
    }

}


void PhysicsScene::update(const float& dt) {


    // Step Physics world by time_step
    b2World_Step(world_id, param::time_step, param::sub_step_count);

    for (int i = 0; i < bodies.size(); ++i) {
        // Sync Sprites to physics position
        sprites[i]->setPosition(b2::invert_height(b2::bv2_to_sv2(b2Body_GetPosition(bodies[i]))));
        // Sync Sprites to physics Rotation
        sprites[i]->setRotation((180.0f / param::pi) * asin(b2Body_GetRotation(bodies[i]).s));
    }
}

void PhysicsScene::render() {
    for (const auto& sprite : sprites) {
        Renderer::queue(sprite.get());
    }
    Scene::render();
}

void PhysicsScene::unload() {
    b2DestroyWorld(world_id);
}

std::shared_ptr<Scene> Scenes::physics;


