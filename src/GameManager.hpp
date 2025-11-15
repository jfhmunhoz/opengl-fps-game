#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Enemy.hpp"
#include "Projectile.hpp"

struct CelestialBody {
    glm::vec3 position;
    float radius;
    float orbitRadius;
    float orbitSpeed; // radians per second
    float rotationSpeed; // radians per second
    float currentOrbitAngle;
    float currentRotationAngle;
    glm::mat4 modelMatrix;
};

class GameManager {
public:
    GameManager();
    void init();
    void update(float deltaTime);
    void render();
    void spawnEnemy(glm::vec3 position);
    void handlePlayerShoot(glm::vec3 shootDir);
    int getScore() const;
    glm::mat4 getMoonTransform() const;
    
private:
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    glm::vec3 targetPosition;
    int score;
    float spawnTimer;
    float spawnInterval;
    
    CelestialBody sun;
    CelestialBody earth;
    CelestialBody moon;
    
    void updateCelestialBodies(float deltaTime);
};

#endif
