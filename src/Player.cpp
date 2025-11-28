#include "Player.hpp"

Player::Player()
    : posX(0.0f), posY(2.0f), posZ(0.0f), nroBalas(6), pontuacao(0), maxAmmo(6), velocity(PLAYER_VELOCITY), collision(false)
{
    Camera camera;
}

void Player::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
}

void Player::setViewDirection(float theta, float phi)
{
    viewTheta = theta;
    viewPhi = phi;
}

glm::vec3 Player::getPosition() const
{
    return glm::vec3(posX, posY, posZ);
}

glm::vec3 Player::getNextPosition(float deltaTime, input_t input)
{
    float vel;

    if(input.aiming)
        vel = SLOWED_VELOCITY;
    else
        vel = velocity;

    float x = viewRadius*cos(viewPhi)*sin(viewTheta);
    float y = viewRadius*sin(viewPhi);
    float z = viewRadius*cos(viewPhi)*cos(viewTheta);

    glm::vec4 player_view_vector = glm::vec4(x, y, z, 0.0f);
    glm::vec4 player_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f);
    glm::vec4 player_side_vector = crossproduct(player_view_vector, player_up_vector);
    glm::vec4 player_direction = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    glm::vec4 player_displacement = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (input.front) player_direction += player_view_vector;
    if (input.back) player_direction -= player_view_vector;
    if (input.right) player_direction += player_side_vector;
    if (input.left) player_direction -= player_side_vector;

    player_displacement = vel * deltaTime *  player_direction;

    return glm::vec3(posX+player_displacement.x, 0.0f, posZ+player_displacement.z);
}

void Player::update(float deltaTime, input_t input)
{
    if(!collision)
    {
        glm::vec3 nextPos = getNextPosition(deltaTime, input);
        posX = nextPos.x;
        posY = nextPos.y;
        posZ = nextPos.z;
    }

    setViewDirection(input.theta, input.phi);

    camera.setCamera(posX, posY+CAMERA_HEIGHT, posZ, viewTheta, viewPhi, input.lookat);
}


glm::vec4 Player::getViewVector()
{
    float x = viewRadius*cos(viewPhi)*sin(viewTheta);
    float y = viewRadius*sin(viewPhi);
    float z = viewRadius*cos(viewPhi)*cos(viewTheta);

    glm::vec4 player_view_vector = glm::vec4(x, y, z, 0.0f);

    return player_view_vector;
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

