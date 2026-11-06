#include "entity.hpp"


Entity::Entity()
    : _position(0.f, 0.f),
    _rotation(0.f),
    _alive(true),
    _visible(true),
    _for_deletion(false)
{
}



void Entity::update(const float& dt)
{
    if (!_alive)
        return;

    for (auto& component : _components)
    {
        component->update(dt);
    }
}

Component::Component(Entity* const p)
    : _parent(p), _for_deletion(false)
{
}

Component::~Component() = default;

bool Component::is_for_deletion() const
{
    return _for_deletion;
}

void Entity::render()
{
    if (!_visible)
        return;

    for (auto& component : _components)
    {
        component->render();
    }
}

const sf::Vector2f& Entity::get_position() const
{
    return _position;
}

void Entity::set_position(const sf::Vector2f& pos)
{
    _position = pos;
}

bool Entity::is_for_deletion() const
{
    return _for_deletion;
}

void Entity::set_for_delete()
{
    _for_deletion = true;
}

float Entity::get_rotation() const
{
    return _rotation;
}

void Entity::set_rotation(float rotation)
{
    _rotation = rotation;
}

bool Entity::is_alive() const
{
    return _alive;
}

void Entity::set_alive(bool alive)
{
    _alive = alive;
}

bool Entity::is_visible() const
{
    return _visible;
}

void Entity::set_visible(bool visible)
{
    _visible = visible;
}

void EntityManager::update(const float& dt)
{
    for (auto& entity : list)
    {
        entity->update(dt);
    }
}

void EntityManager::render()
{
    for (auto& entity : list)
    {
        entity->render();
    }
}
