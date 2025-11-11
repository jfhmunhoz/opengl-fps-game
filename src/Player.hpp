#include "Camera.hpp"
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
private:
    // Posicao player
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    Camera camera;
    int nroBalas = 30;
    int pontuacao = 0;
    void reload();
    void shot();
    void resetPoints();
    void addPoints();
    
    // float cameraTheta = 0.0f;
    // float cameraPhi = 0.0f;
}

#endif
