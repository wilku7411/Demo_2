#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Gui.h"
#include "Timer.h"
#include "IO/Window.h"
#include "graphics/Light.h"
#include "graphics/Model.h"
#include "graphics/PartialScene.h"
#include "graphics/Shader.h"
#include "graphics/Primitives.h"

#include "objects/Asteroid.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

glm::vec3 g_lightCasterPosition{ 0.0f, 10.0f, 0.0f };
glm::vec3 g_cameraPos{ 0.0f, 1.0f, 0.0f };
glm::vec3 g_lightColor{ 1.0f, 1.0f, 1.0f };
float g_ambientStrength = 0.4f;


unsigned int loadTexture(char const * path);
unsigned int loadCubemap(const std::vector<std::string>& faces);

int main()
{
    CWindow mainWindow;
    mainWindow.Init("Demo", 1600, 900, false);
    
    CGui gui(&mainWindow);

    // World origin
	COriginGizmo sceneOrigin;

    /* Scene component creation */
    CPartialScene shipScene;
	shipScene.Name("Spaceship");

	CModel ship_model("source/resources/meshes/rakietka_cudowna.obj");
    CMaterial ship_material("source/resources/shaders/basic.vert", "source/resources/shaders/basic.frag");
    CLight ship_point_light = CLight(g_lightCasterPosition, g_cameraPos, g_lightColor, g_ambientStrength);
	CLight* asteroid_point_light = &ship_point_light;
	
    // Attaching observers
	ship_model.Attach(&ship_material);
	ship_point_light.Attach(&ship_material);

	// Putting it all together
    shipScene.Init(&ship_model, &ship_material, &ship_point_light);


	// Main renderer projection matrix
	glm::mat4 rendererProjectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 1.0f, 100.0f);
    ship_material.UpdateProjectionMatrix(rendererProjectionMatrix);
	
    shipScene.GetModel().transformOrigin.UpdateMatrices(rendererProjectionMatrix, glm::mat4{ 1.0f }, glm::mat4{ 1.0f });
    
    CMaterial orbiter_material("source/resources/shaders/defaultVS.shader", "source/resources/shaders/defaultFS.shader");
    orbiter_material.UpdateProjectionMatrix(rendererProjectionMatrix);
	
    // Quick check if asteroids and trajectory info works correctly
    std::vector<Object::CAsteroid> orbiters{
        { "Companion sphere 1", &orbiter_material },
        { "Companion sphere 2", &orbiter_material },
        { "Companion sphere 3", &orbiter_material },
        { "Companion sphere 4", &orbiter_material },
        { "Companion sphere 5", &orbiter_material },
        { "Companion sphere 6", &orbiter_material }
    };

    for (auto it = orbiters.begin(); it != orbiters.end(); it++)
    {
        it->Init(rendererProjectionMatrix, asteroid_point_light);
    }

	orbiters[0].GetModel().SetObjectColor({ 0.1f, 0.0f, 0.1f });
    orbiters[1].GetModel().SetObjectColor({ 0.1f, 0.0f, 0.1f });
    orbiters[2].GetModel().SetObjectColor({ 0.1f, 0.0f, 0.1f });
    orbiters[3].GetModel().SetObjectColor({ 0.1f, 0.0f, 0.1f });

    orbiters[0].GetTrajectoryInfo()->orbit_tilt = 10.0f;
    orbiters[1].GetTrajectoryInfo()->orbit_tilt = 10.0f;
    orbiters[2].GetTrajectoryInfo()->orbit_tilt = 6.0f;
    orbiters[3].GetTrajectoryInfo()->orbit_tilt = 6.0f;
    
    orbiters[4].GetTrajectoryInfo()->orbit_tilt = 0.0f;
    orbiters[5].GetTrajectoryInfo()->orbit_tilt = 0.0f;

    orbiters[0].GetTrajectoryInfo()->orbit_radius = 4.0f;
    orbiters[1].GetTrajectoryInfo()->orbit_radius = 4.0f;
    orbiters[2].GetTrajectoryInfo()->orbit_radius = 6.0f;
    orbiters[3].GetTrajectoryInfo()->orbit_radius = 6.0f;

    orbiters[0].GetTrajectoryInfo()->speed_factor += 0.0f;
    orbiters[1].GetTrajectoryInfo()->speed_factor += 0.0f;
    orbiters[2].GetTrajectoryInfo()->speed_factor += 3.0f;
    orbiters[3].GetTrajectoryInfo()->speed_factor += 3.0f;

    orbiters[0].GetTrajectoryInfo()->speed_factor *= -1.0f;
    orbiters[2].GetTrajectoryInfo()->speed_factor *= -1.0f;
    orbiters[4].GetTrajectoryInfo()->speed_factor *= -1.0f;
    orbiters[5].GetTrajectoryInfo()->speed_factor *= -1.0f;

    orbiters[5].GetTrajectoryInfo()->speed_factor *= -1.0f;

    glm::mat4 cameraMatrix;
	cameraMatrix = glm::translate(cameraMatrix, g_cameraPos * 5.0f);
	Camera::cameraPos = glm::vec3{ cameraMatrix[3].x, cameraMatrix[3].y, cameraMatrix[3].z };

    // Attaching controller for shipScene
    CController ship_controller(&mainWindow, &ship_model.GetModelMatRef(), &ship_model.GetViewMatRef());
    shipScene.AttachController(&ship_controller);


    glm::vec3* toStalk = nullptr;
    glm::vec3 cameraFactor{ 20.0f, -20.0f, 2.0f };

	while (mainWindow.IsOpen())
	{
        g_mainTimer.Update();
		mainWindow.ClearUpdate();

		glm::vec3 shipPos =
		{
			shipScene.GetModel().GetModelMat()[3].x,
			shipScene.GetModel().GetModelMat()[3].y,
			shipScene.GetModel().GetModelMat()[3].z
		};
    	Camera::cameraPos = shipPos - cameraFactor;
		
        if(glfwGetKey(mainWindow, GLFW_KEY_LEFT_BRACKET))
        {
            toStalk = &shipPos;
        }
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT_BRACKET))
        {
            toStalk = orbiters[0].GetPosition();
        }

        if (toStalk == nullptr)
            toStalk = &shipPos;
        cameraMatrix = Camera::lookAt(*toStalk);
		
		shipScene.GetModel().SetViewMat(cameraMatrix);

		shipScene.UpdateInput();
		shipScene.Update();
        shipScene.Draw();
        
        for (auto it = orbiters.begin(); it != orbiters.end(); it++)
        {
            it->GetModel().SetViewMat(cameraMatrix);
		    it->Update(shipPos);
		    it->Draw();
        }

		mainWindow.ProcessKeyboardInput();

        gui.Draw(&ship_material);
        
        for (auto it = orbiters.begin(); it != orbiters.end(); it++)
        {
            it->DrawDebugGizmos();
        }

        shipScene.DrawDebugGizmos();
        
		sceneOrigin.UpdateMatrices(rendererProjectionMatrix, cameraMatrix, glm::mat4{ 1.0f });
		sceneOrigin.Draw();

        mainWindow.Swap();
        glfwPollEvents();
    } 

    gui.Destroy();

    mainWindow.Destroy();
    return 0;
}


unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load cubemap texture: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(const std::vector<std::string>& faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load cubemap texture: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
