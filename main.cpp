#include "game_system.hpp"
#include "game_parameters.hpp"
#include "scenes.hpp"

namespace param = Parameters;

int main()
{
    Scenes::physics = std::make_shared<PhysicsScene>();
    Scenes::physics->load();
    GameSystem::set_active_scene(Scenes::physics);

    GameSystem::start(param::game_width, param::game_height, "Coursework Practice", 1.0f / 60.f);
}
