#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.hpp"
#include <glm/glm.hpp>

#define PLAYER_VELOCITY 5.0f
#define SLOWED_VELOCITY 2.0f
#define CAMERA_HEIGHT 2.0f

typedef struct input
{
    bool front=false;
    bool back=false;
    bool right=false;
    bool left=false;
    float theta=0.0f;
    float phi=0.0f;

    bool aiming=false;
    bool lookat=false;
} input_t;

class Player
{
public:
    Player();

    void update(float deltaTime, input_t input);

    glm::vec3 getPosition() const;
    glm::vec4 getViewVector();
    int getAmmo() const;
    int getScore() const;
    int getMaxAmmo() const;
    glm::vec3 getNextPosition(float deltaTime, input_t input);
    bool isAlive();

    void setPosition(float x, float y, float z);
    void setViewDirection(float theta, float phi);
    void setColision(bool collided);

    void shoot(float time);
    void reload();
    void addScore(int points);
    float gunAnimation(float time);
    void dead();

    Camera& getCamera();
    
private:
    bool alive = true;
    // Posicao player
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;
    float velocity;
    bool collision = false;

    float viewRadius = 2.5f;
    float viewTheta;
    float viewPhi;

    Camera camera;
    int nroBalas;
    int pontuacao;
    int maxAmmo;
    float prevShotTime = 0;
    bool shooting = false;
    
    void resetPoints();
    void addPoints();
};

#endif
