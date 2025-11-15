#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <cmath>

class Camera {
public:
	Camera();
	void setPosition(float x, float y, float z);
	void setViewDirection(float theta, float phi);
	glm::vec3 getPosition() const;
	glm::vec3 getViewDirection() const;
	void setPerspective(bool perspective);
	void setFOV(float newFov);
	float getFOV() const;
	float getNearPlane() const;
	float getFarPlane() const;
	bool isPerspective() const;

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
	
	void updateViewVector();
};

#endif
