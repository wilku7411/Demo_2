#include "Window.h"


int CWindow::Init(const std::string& windowName, const int width, const int height, bool fullscreen)
{
    if(InitGLFW() == 0)
		return 0;

	if(!fullscreen)
		m_window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
	else
		m_window = glfwCreateWindow(width, height, windowName.c_str(), glfwGetPrimaryMonitor(), NULL);

	if (InitContext() == 0)
		return 0;

	m_open = true;

    SetHints();

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
    SetCallbacks();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CWindow::Destroy()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void CWindow::ClearUpdate()
{
	// Dark blue background
    glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], m_backgroundColor[3]);

	// Clear the color and depth buffer of current framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CWindow::Update()
{

}

void CWindow::Swap() 
{
	// Swap buffers
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void CWindow::ProcessKeyboardInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_open = false;
	}

	if (glfwGetKey(m_window, GLFW_KEY_KP_0) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(m_window, GLFW_KEY_KP_1) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void CWindow::SetCallbacks()
{
    glfwSetScrollCallback(m_window, MouseScrollCallback);
	glfwSetWindowSizeCallback(m_window, ViewPortChangeCallback);
}

void CWindow::SetPosition(EScreenPos position)
{
    switch (position)
    {
        case EScreenPos::UPPER_LEFT:
        {
            glfwSetWindowPos(m_window, 0, 0);
            break;
        }

        case EScreenPos::UPPER_RIGHT:
        {
            glfwSetWindowPos(m_window, m_desktopMode->width - m_width, 0);
            break;
        }

        case EScreenPos::LOWER_LEFT:
        {
            glfwSetWindowPos(m_window, 0, m_desktopMode->height - m_height);
            break;

        }

        case EScreenPos::LOWER_RIGHT:
        {
            glfwSetWindowPos(m_window, m_desktopMode->width - m_width, m_desktopMode->height - m_height);
            break;
        }

        case EScreenPos::CENTER:
        {
            glfwSetWindowPos(
                m_window, 
                m_desktopMode->width - m_width/2 - m_width/2, 
                m_desktopMode->height - m_height/2 - m_height/2
            );
            break;
        }

        default:
        {
            glfwSetWindowPos(m_window, 0, 0);
            break;
        }
    }
}


void CWindow::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    //VerticalScroll(yoffset);
}

void CWindow::ViewPortChangeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int CWindow::InitGLFW()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return 0;
    }
    return 1;
}

int CWindow::InitContext()
{
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize context. [GLAD] \n");
        glfwTerminate();
        return 0;
    }
    return 1;
}

void CWindow::SetHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
