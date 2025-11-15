#include "Player.hpp"

Player::Player()
    : posX(0.0f), posY(0.0f), posZ(0.0f), nroBalas(30), pontuacao(0), maxAmmo(30)
{
}

void Player::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
    camera.setPosition(x, y, z);
}

glm::vec3 Player::getPosition() const
{
    return glm::vec3(posX, posY, posZ);
}

void Player::update(float deltaTime)
{
    // Update player logic here
    // Movement, camera updates, etc.
}

void Player::shoot()
{
    if (nroBalas > 0) {
        nroBalas--;
    }
}

void Player::reload()
{
    nroBalas = maxAmmo;
}

int Player::getAmmo() const
{
    return nroBalas;
}

int Player::getScore() const
{
    return pontuacao;
}

void Player::addScore(int points)
{
    pontuacao += points;
}

Camera& Player::getCamera()
{
    return camera;
}

void Player::resetPoints()
{
    pontuacao = 0;
}

void Player::addPoints()
{
    pontuacao++;
}
