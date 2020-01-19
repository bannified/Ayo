#include "ayopch.h"
#include "Time.h"
#include "glfw/glfw3.h"

double Ayo::Time::m_DeltaTime = 0.0f;
double Ayo::Time::m_TimeLastFrame = 0.0f;

void Ayo::Time::Initialize()
{
    m_TimeLastFrame = glfwGetTime();
    m_DeltaTime = 0.0f;
}

void Ayo::Time::Update()
{
    double currentFrame = glfwGetTime();
    m_DeltaTime = currentFrame - m_TimeLastFrame;
    m_TimeLastFrame = currentFrame;
}
