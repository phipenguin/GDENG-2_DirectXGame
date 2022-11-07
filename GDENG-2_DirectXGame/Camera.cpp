#include "Camera.h"
#include "InputSystem.h"
#include <iostream>

Camera::Camera(string name) : AGameObject(name)
{
    this->setPosition(0.0f, 0.0f, -2.0f);
    //this->setPosition(5.0f, 3.0f, -5.0f);
    //this->setRotation(0.3f, -0.8f, this->getLocalRotation().m_z);
    //this->setRotation(0.4f, -0.5f, this->getLocalRotation().m_z);
    this->updateViewMatrix();
    InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
    InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
    Vector3D localPos = this->getLocalPosition();
    float x = localPos.m_x;
    float y = localPos.m_y;
    float z = localPos.m_z;
    float moveSpeed = 10.0f;

    if (InputSystem::getInstance()->isKeyDown('W'))
    {
        z += deltaTime * moveSpeed;
        this->setPosition(x, y, z);
        this->updateViewMatrix();
    }
    else if (InputSystem::getInstance()->isKeyDown('S'))
    {
        z -= deltaTime * moveSpeed;
        this->setPosition(x, y, z);
        this->updateViewMatrix();
    }
    else if (InputSystem::getInstance()->isKeyDown('A'))
    {
        x -= deltaTime * moveSpeed;
        this->setPosition(x, y, z);
        this->updateViewMatrix();
    }
    else if (InputSystem::getInstance()->isKeyDown('D'))
    {
        x += deltaTime * moveSpeed;
        this->setPosition(x, y, z);
        this->updateViewMatrix();
    }
}

void Camera::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
}

Matrix4x4 Camera::getViewMatrix()
{
    return this->localMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point& delta_mouse_pos)
{
    if (this->mouseDown)
    {
        Vector3D localRot = this->getLocalRotation();
        float x = localRot.m_x;
        float y = localRot.m_y;
        float z = localRot.m_z;

        float speed = 0.005f;
        x += delta_mouse_pos.m_y * speed;
        y += delta_mouse_pos.m_x * speed;

        this->setRotation(x, y, z);
        std::cout << "Camera Rotation: " << "(" << this->getLocalRotation().m_x << ", " << this->getLocalRotation().m_y << ", " << this->getLocalRotation().m_z << ")" << std::endl;
        this->updateViewMatrix();
    }
}

void Camera::onLeftMouseDown(const Point& mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point& mouse_pos)
{
}

void Camera::onRightMouseDown(const Point& mouse_pos)
{
    this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point& mouse_pos)
{
    this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
    Matrix4x4 worldCam; worldCam.setIdentity();
    Matrix4x4 temp; temp.setIdentity();

    Vector3D localRot = this->getLocalRotation();

    temp.setRotationX(localRot.m_x);
    worldCam *= temp;
    
    temp.setRotationY(localRot.m_y);
    worldCam *= temp;

    temp.setTranslation(this->getLocalPosition());
    worldCam *= temp;

    worldCam.inverse();
    this->localMatrix = worldCam;
}