#include "Camera.hpp"

Camera::Camera()
    : perspectiveProjection(true), fov(45.0f), nearplane(0.1f), farplane(100.0f),
      cameraDistance(1.0f), top(1.0f), bottom(-1.0f), right(1.0f), left(-1.0f)
{
    updateViewVector();
}

void Camera::updateViewVector()
{
    viewX = viewRadius * sin(viewTheta) * cos(viewPhi);
    viewY = viewRadius * sin(viewPhi);
    viewZ = viewRadius * cos(viewTheta) * cos(viewPhi);
}

void Camera::setPosition(float x, float y, float z)
{
    cameraX = x;
    cameraY = y;
    cameraZ = z;
}

void Camera::setViewDirection(float theta, float phi)
{
    viewTheta = theta;
    viewPhi = phi;
    updateViewVector();
}

glm::vec3 Camera::getPosition() const
{
    return glm::vec3(cameraX, cameraY, cameraZ);
}

glm::vec3 Camera::getViewDirection() const
{
    return glm::vec3(viewX, viewY, viewZ);
}

void Camera::setPerspective(bool perspective)
{
    perspectiveProjection = perspective;
}

void Camera::setFOV(float newFov)
{
    fov = newFov;
}

float Camera::getFOV() const
{
    return fov;
}

float Camera::getNearPlane() const
{
    return nearplane;
}

float Camera::getFarPlane() const
{
    return farplane;
}

bool Camera::isPerspective() const
{
    return perspectiveProjection;
}
