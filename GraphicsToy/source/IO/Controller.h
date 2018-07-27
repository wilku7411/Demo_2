#pragma once

#include "Window.h"
#include "../Timer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

class CController
{
public:
    CController(CWindow* window, glm::mat4* modelMat, glm::mat4* viewMat)
        :
        m_windowRef(window),
        m_modelRef(modelMat),
        m_viewRef(viewMat)
    {};

    virtual void InputUpdate();

private:
    CWindow* m_windowRef;
    glm::mat4* m_modelRef;
    glm::mat4* m_viewRef;
};