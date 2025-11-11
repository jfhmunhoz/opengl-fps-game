#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:

private:
	//perspective
	bool perspectiveProjection;
	float field_of_view;
	float nearplane;
	float farplane;

	//orto
	float cameraDistance;
	float t;
	float b;
	float r;
	float l;

	//Posicao da camera
	float cameraX = 0.0f;
	float cameraY = 0.5f;
	float cameraZ = -3.0f;

	float cameraTheta = 0.0f;
	float cameraPhi = 0.0f;

	//View Vector
	float ViewRadius = 2.5f;
	float ViewTheta = 0.0f;
	float ViewPhi = 0.0f;

	float ViewX;
	float ViewY;
	float ViewZ;
}

#endif
