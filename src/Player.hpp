#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.hpp"
#include <glm/glm.hpp>

class Player
{
public:
    Player();
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() const;
    void update(float deltaTime);
    int getMaxAmmo() const;
    void shoot(float time);
    void reload();
    int getAmmo() const;
    int getScore() const;
    void addScore(int points);
    float gunAnimation(float time);

    Camera& getCamera();
    
private:
    // Posicao player
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    Camera camera;
    int nroBalas = 6;
    int pontuacao = 0;
    int maxAmmo = 6;
    float prevShotTime = 0;
    bool shooting = false;
    
    void resetPoints();
    void addPoints();
};

#endif
