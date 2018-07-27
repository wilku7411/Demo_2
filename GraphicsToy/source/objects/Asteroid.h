#pragma once

#include "../graphics/PartialScene.h"

namespace Object
{
    struct STrajectory
    {
        glm::vec3 center_of_orbit;
        float orbit_radius = 10.0f;
        float orbit_tilt = 1.0f;
        float speed_factor = 2.0f;
        float angular_velocity = 0.0f;

        void BindAttractor(glm::vec3 attractor)
        {
            center_of_orbit = attractor;
        }

        glm::vec3 Update()
        {
            angular_velocity += g_mainTimer.deltaTime * speed_factor;

            return glm::vec3{
                center_of_orbit.x + glm::cos(angular_velocity) * orbit_radius,
                center_of_orbit.y + glm::cos(angular_velocity) * orbit_tilt, 
                center_of_orbit.z + glm::sin(angular_velocity) * orbit_radius
            };
        }
    };


    class CAsteroid : public CPartialScene
    {
	private:
        using Super = CPartialScene;

    public:
        CAsteroid() 
            : 
            Super() 
        {};
        CAsteroid(const CAsteroid& other) = default;
        CAsteroid(CAsteroid&& other) = default;
        virtual ~CAsteroid();
        CAsteroid& operator=(CAsteroid& other) = default;

        CAsteroid(const std::string& name, CMaterial* material = nullptr);

        void Init(glm::mat4 projection, CLight* pointLight);

        void Update(glm::vec3 attractor);

        void Draw();
        void Draw(unsigned int shaderID);

        glm::vec3* GetPosition();
        STrajectory* GetTrajectoryInfo() { return &m_traj; };
    private:
        STrajectory m_traj;
        glm::vec3 m_position;
        const char* asteroid_mesh = "source/resources/meshes/asteroid.obj";
        const char* asteroid_vs = "source/resources/shaders/defaultVS.shader";
        const char* asteroid_fs = "source/resources/shaders/defaultFS.shader";
    };
};