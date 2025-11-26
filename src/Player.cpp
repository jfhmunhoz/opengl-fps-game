#include "Player.hpp"

Player::Player()
    : posX(0.0f), posY(2.0f), posZ(0.0f), nroBalas(6), pontuacao(0), maxAmmo(6)
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

int Player::getMaxAmmo() const
{
    return maxAmmo;
}

void Player::shoot(float time)
{
    if (nroBalas > 0) {
        if(time - prevShotTime > 0.5f)
        {
            nroBalas--;
            prevShotTime = time;
        }
    }
}

float Player::gunAnimation(float time)
{
    if(time - prevShotTime > 0.5f)
    {
        return 0.0f;
    }
    else
    {
        return (time - prevShotTime)/0.5f;
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
