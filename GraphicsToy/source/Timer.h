#pragma once

#include "stdio.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct STimer
{
    STimer()
        :
        current_time(0.0),
        previous_time(0.0),
        deltaTime(0.0),
        num_of_frames(0.0),
        counter(0.0)
    {
        Update();
    }

    void Update()
    {
        CalculateDeltaTime();
    }

    double current_time;
    double previous_time;
    double deltaTime;
    double num_of_frames;
    double counter;

private:

    inline void CalculateDeltaTime()
    {
        previous_time = current_time;
        current_time = glfwGetTime();
        counter += deltaTime;
        deltaTime = current_time - previous_time;
    }
};

extern STimer g_mainTimer;