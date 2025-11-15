#include "GameManager.hpp"
#include "collisions.hpp"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cmath>

GameManager::GameManager()
    : targetPosition(0.0f, 1.0f, 5.0f), score(0), spawnTimer(0.0f), spawnInterval(2.0f)
{
    // Initialize Sun (stationary at origin)
    sun.position = glm::vec3(0.0f);
    sun.radius = 10.0f;
    sun.orbitRadius = 0.0f;
    sun.orbitSpeed = 0.0f;
    sun.rotationSpeed = 0.1f;
    sun.currentOrbitAngle = 0.0f;
    sun.currentRotationAngle = 0.0f;
    
    // Initialize Earth (orbits sun)
    earth.position = glm::vec3(50.0f, 0.0f, 0.0f);
    earth.radius = 4.0f;
    earth.orbitRadius = 50.0f;
    earth.orbitSpeed = 0.3f; // slow orbit
    earth.rotationSpeed = 0.5f;
    earth.currentOrbitAngle = 0.0f;
    earth.currentRotationAngle = 0.0f;
    
    // Initialize Moon (orbits earth)
    moon.position = earth.position + glm::vec3(10.0f, 0.0f, 0.0f);
    moon.radius = 1.0f;
    moon.orbitRadius = 10.0f;
    moon.orbitSpeed = 2.0f; // faster orbit around earth
    moon.rotationSpeed = 0.2f;
    moon.currentOrbitAngle = 0.0f;
    moon.currentRotationAngle = 0.0f;
}

void GameManager::init()
{
    // Initialize game state
}

void GameManager::updateCelestialBodies(float deltaTime)
{
    // Update Earth orbit around Sun
    earth.currentOrbitAngle += earth.orbitSpeed * deltaTime;
    earth.position = glm::vec3(
        cos(earth.currentOrbitAngle) * earth.orbitRadius,
        0.0f,
        sin(earth.currentOrbitAngle) * earth.orbitRadius
    );
    earth.currentRotationAngle += earth.rotationSpeed * deltaTime;
    earth.modelMatrix = glm::translate(glm::mat4(1.0f), earth.position);
    earth.modelMatrix = glm::rotate(earth.modelMatrix, earth.currentRotationAngle, glm::vec3(0, 1, 0));
    
    // Update Moon orbit around Earth
    moon.currentOrbitAngle += moon.orbitSpeed * deltaTime;
    glm::vec3 moonLocalPos = glm::vec3(
        cos(moon.currentOrbitAngle) * moon.orbitRadius,
        0.0f,
        sin(moon.currentOrbitAngle) * moon.orbitRadius
    );
    moon.position = earth.position + moonLocalPos;
    moon.currentRotationAngle += moon.rotationSpeed * deltaTime;
    moon.modelMatrix = glm::translate(glm::mat4(1.0f), moon.position);
    moon.modelMatrix = glm::rotate(moon.modelMatrix, moon.currentRotationAngle, glm::vec3(0, 1, 0));
}

glm::mat4 GameManager::getMoonTransform() const
{
    return moon.modelMatrix;
}

void GameManager::update(float deltaTime)
{
    // Update celestial bodies first
    updateCelestialBodies(deltaTime);
    
    // Update enemies
    for (auto& enemy : enemies) {
        enemy.update(deltaTime);
    }
    
    // Update projectiles
    for (auto& projectile : projectiles) {
        projectile.update(deltaTime);
    }
    
    // Check collisions between projectiles and enemies
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        bool hit = false;
        for (auto& enemy : enemies) {
            if (CollisionManager::rayToSphere(it->getPosition(), glm::vec3(0, 0, 1),
                                              enemy.getPosition(), 0.5f)) {
                enemy.takeDamage(50.0f);
                hit = true;
                break;
            }
        }
        if (hit || !it->isActive()) {
            it = projectiles.erase(it);
        } else {
            ++it;
        }
    }
    
    // Remove dead enemies
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!it->isAlive()) {
            score += 10;
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
    
    // Spawn enemies
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        float x = -5.0f + (rand() % 100) / 10.0f;
        float z = -5.0f + (rand() % 100) / 10.0f;
        spawnEnemy(glm::vec3(x, 1.0f, z));
        spawnTimer = 0.0f;
    }
}

void GameManager::render()
{
    for (auto& enemy : enemies) {
        enemy.render();
    }
    
    for (auto& projectile : projectiles) {
        projectile.render();
    }
}

void GameManager::spawnEnemy(glm::vec3 position)
{
    enemies.emplace_back(position, targetPosition);
}

void GameManager::handlePlayerShoot(glm::vec3 shootDir)
{
    projectiles.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f), shootDir);
}

int GameManager::getScore() const
{
    return score;
}
