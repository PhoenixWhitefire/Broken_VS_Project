//A class used for representing the player's camera/main camera
//lmao half of this class's functionality was removed from it because i moved it to places where it made more sense

#ifndef CLASS_CAMERA
#define CLASS_CAMERA

#include"ShaderProgram.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Vector2Int.h"

class Camera {
	public:
		glm::vec3 Position;
		glm::vec3 LookVec = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 UpVec = glm::vec3(0.0f, 1.0f, 0.0f);

		bool FirstClick = true;

		int WindowWidth;
		int WindowHeight;

		float CameraSpeed = 200.0f;
		float Speed;

		float NearPlane = 0.1f;
		float FarPlane = 1000.0f;

		float FOV = 45.0f;

		float MouseSensitivity = 100.0f;

		glm::mat4 Matrix = glm::mat4(1.0f);

		Camera(Vector2Int WindowSize);

		void Update();
};

#endif
