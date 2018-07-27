#pragma once

struct SBasicUniforms
{
	// Transformations
	unsigned int modelMatrix;
	unsigned int viewMatrix;
	unsigned int projectionMatrix;

	// Light
	unsigned int lightPosition;
	unsigned int lightColor;
	unsigned int ambientStrength;
    unsigned int specularStrength;
    unsigned int shininess;
    
	// Camera
	unsigned int cameraPosition;
	
	// Model
	unsigned int objectColor;


    inline void SetAll(
        unsigned int MMat,
        unsigned int VMat,
        unsigned int PMat,
        unsigned int lightPos,
        unsigned int lightCol,
        unsigned int ambientStr,
        unsigned int specularStr,
        unsigned int shine,
		unsigned int cameraPos,
		unsigned int objectCol
	)
	{
		modelMatrix = MMat;
		viewMatrix = VMat;
		projectionMatrix = PMat;
		lightPosition = lightPos;
		lightColor = lightCol;
		ambientStrength = ambientStr;
        specularStrength = specularStr;
        shininess = shine;
		cameraPosition = cameraPos;
		objectColor = objectCol;
	}

	SBasicUniforms& operator=(const SBasicUniforms& other) = default;
};

