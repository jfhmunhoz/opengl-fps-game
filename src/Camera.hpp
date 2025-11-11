#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:

private:
	bool perspectiveProjection;

	//Posicao da camera
	float g_CameraX = 0.0f;
	float g_CameraY = 0.5f;
	float g_CameraZ = -3.0f;

	//View Vector
	float g_ViewRadius = 2.5f;
	float g_ViewTheta = 0.0f;
	float g_ViewPhi = 0.0f;

	float g_ViewX;
	float g_ViewY;
	float g_ViewZ;
}

#endif
