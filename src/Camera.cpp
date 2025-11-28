#include "Camera.hpp"

Camera::Camera()
    : perspectiveProjection(true), fov(45.0f), nearplane(0.1f), farplane(100.0f),
      cameraDistance(1.0f), top(1.0f), bottom(-1.0f), right(1.0f), left(-1.0f)
{
}


void Camera::setCamera(float x, float y, float z, float theta, float phi, bool lookat)
{
    cameraX = x;
    cameraY = y;
    cameraZ = z;
    cameraTheta = theta;
    cameraPhi = phi;
    cameraLookAt = lookat;
}


glm::vec4 Camera::getPosition() const
{
    float x, y, z;
    if(cameraLookAt)
    {
        x = cameraX+cameraRadius*cos(cameraPhi)*sin(cameraTheta);
        y = cameraY+cameraRadius*sin(cameraPhi);
        z = cameraZ+cameraRadius*cos(cameraPhi)*cos(cameraTheta);
    }
    else
    {
        x = cameraX;
        y = cameraY;
        z = cameraZ;
    }
    return glm::vec4(x, y, z, 1.0f);
}

glm::vec4 Camera::getView() const
{
    float x, y, z;
    if(cameraLookAt)
    {
        x =-cameraRadius*cos(cameraPhi)*sin(cameraTheta);
        y =-cameraRadius*sin(cameraPhi);
        z =-cameraRadius*cos(cameraPhi)*cos(cameraTheta);
    }
    else
    {
        x = cameraRadius*cos(cameraPhi)*sin(cameraTheta);
        y = cameraRadius*sin(cameraPhi);
        z = cameraRadius*cos(cameraPhi)*cos(cameraTheta);
    }
    return glm::vec4(x, y, z, 0.0f);
}

float Camera::getTheta()
{
    return cameraTheta;
}

float Camera::getPhi()
{
    return cameraPhi;
}

bool Camera::isLookAt()
{
    return cameraLookAt;
}

glm::vec4 Camera::getUpVector() const
{
    return glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
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
