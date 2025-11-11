#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:

private:
	//perspective
	bool perspectiveProjection;
	float fov;
	float nearplane;
	float farplane;

	//orto
	float cameraDistance;
	float top;
	float bottom;
	float right;
	float left;

	//Posicao da camera
	float cameraX = 0.0f;
	float cameraY = 0.5f;
	float cameraZ = -3.0f;

	float cameraTheta = 0.0f;
	float cameraPhi = 0.0f;

	//View Vector
	float viewRadius = 2.5f;
	float viewTheta = 0.0f;
	float viewPhi = 0.0f;

	float viewX;
	float viewY;
	float viewZ;
}

#endif
