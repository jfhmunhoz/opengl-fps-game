#include "Projectile.hpp"

Projectile::Projectile(glm::vec3 position, glm::vec3 direction)
    : position(position), direction(glm::normalize(direction)), speed(30.0f), 
      lifetime(0.0f)
{
}

void Projectile::update(float deltaTime)
{
    position += direction * speed * deltaTime;
    lifetime += deltaTime;
}

void Projectile::render()
{
    // TODO: Implement rendering (small sphere or marker)
}

glm::vec3 Projectile::getPosition() const
{
    return position;
}

bool Projectile::isActive() const
{
    return lifetime < 5.0f;
}
