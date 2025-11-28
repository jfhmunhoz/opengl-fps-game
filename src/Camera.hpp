#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <cmath>

class Camera {
public:
	Camera();
	void setCamera(float x, float y, float z, float theta, float phi, bool lookat);
	glm::vec4 getPosition() const;
	glm::vec4 getView() const;
	float getTheta();
	float getPhi();
	bool isLookAt();
	glm::vec4 getUpVector() const;
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
	bool cameraLookAt = false;
	float cameraX = 0.0f;
	float cameraY = 0.5f;
	float cameraZ = -3.0f;
	float cameraTheta;
	float cameraPhi;
	float cameraRadius = 2.5f;
};

#endif
