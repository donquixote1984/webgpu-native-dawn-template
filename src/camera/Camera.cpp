#include "Camera.h"
#include "../Scene.h"

void Camera::onProcessInput(GLFWwindow *window) 
{
    float cameraSpeed = .05f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Position 	   += cameraSpeed * m_CamFront;
		//m_Offset.z += cameraSpeed * m_CamFront.z;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_Position 	 -= cameraSpeed * glm::cross(m_CamFront, m_CamUp);
			m_Offset -= cameraSpeed * glm::cross(m_CamFront, m_CamUp);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_Position -= cameraSpeed * m_CamFront;
			m_Translate = m_Position - m_InitPos;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_Position    += cameraSpeed * glm::cross(m_CamFront, m_CamUp);
			m_Offset += cameraSpeed * glm::cross(m_CamFront, m_CamUp);
		}	

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			m_Position    += cameraSpeed * m_CamUp;
			//m_Offset += cameraSpeed * glm::cross(m_CamFront, m_CamUp);
			m_Offset.y += cameraSpeed * m_CamUp.y;
		}	

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			m_Position    -= cameraSpeed * m_CamUp;
			m_Offset.y -= cameraSpeed * m_CamUp.y;
		}	
	}
}

void Camera::onMouseMove(double x, double y)
{
	if (m_FirstMouse) {
		m_LastMouseX = x ;
		m_LastMouseY = y ;
		m_FirstMouse = false;
		//m_Offset = m_Pos;

		//m_Pos = glm::length(m_Pos - m_Offset) * -m_CamFront + m_Offset + m_InitPos;
		return;
	}

	float xOffset = x - m_LastMouseX;
	float yOffset = m_LastMouseY - y;
	if(xOffset == .0f && yOffset == .0f)
	{
		return;
	}


	m_LastMouseX = x;
	m_LastMouseY = y;

	float sensitivity = 0.2f;
	xOffset *= sensitivity;
    yOffset *= sensitivity;

	m_RotateY -= xOffset;
	m_RotateX -= yOffset;

	m_RotateX = std::clamp(m_RotateX, -89.0f, 89.0f);
	//m_Yaw = std::clamp(m_Yaw, -89.0f, 89.0f);

	glm::vec3 front;


	//front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	//front.y = sin(glm::radians(m_Pitch)); 
	//front.z = 0; //cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));


	//std::cout << front.x <<  ", " << front.y << ", " << front.z << std::endl;

	glm::quat yRot = glm::angleAxis(glm::radians(xOffset), glm::vec3(0, -1, 0));
	glm::quat xRot = glm::angleAxis(glm::radians(yOffset), glm::vec3(1, 0, 0));

	m_Position = xRot * m_Position;
	m_Position = yRot * m_Position;
	m_CamFront = -glm::normalize(m_Position);
	//m_CamFront = glm::normalize(m_InitCamFront+ glm::vec3(m_Yaw, m_Pitch, 0));
	//m_Position = glm::length(m_Position - m_Offset) * -m_CamFront + m_Offset;
	//m_Position = -m_FocalLength * m_CamFront;
	this->UpdateScene();
}

void Camera::OnUpdate(GLFWwindow *window)
{
	onProcessInput(window);
	//m_Scene->Bind();
	//Shader *shader = m_Scene->GetShader();	
	//shader->setUniform4m("projection", m_Projection);
	//shader->setUniform4m("view", getView());
	//shader->setUniform3f("camPos", m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::UpdateScene()
{
	Scene::GetInstance()->ShouldUpdate();
}