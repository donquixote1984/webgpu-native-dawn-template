#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "BaseObject.h"
class TransformObject: public BaseObject
{
protected:
    glm::mat4 m_Model =  glm::mat4(1.0f);
    glm::vec3 m_Position = glm::vec3(0.0f);
    glm::vec3 m_Scale=glm::vec3(1.0);
    glm::quat m_Rotate = glm::angleAxis(0.0f, glm::vec3(0, 1, 0));
    glm::vec3 m_InitScale = glm::vec3(1.0);
    glm::mat4 m_TransMat;
public:
    void Scale(glm::vec3);
    void Translate(glm::vec3);
    void Rotate(float, glm::vec3);
    void Rotate(glm::quat rot);
    void Rotate(glm::vec3);
    void RotateRadians(glm::vec3 axisAndAngles);
    void SetPosition(glm::vec3);
    void CalcModelMat();
    glm::mat4 & GetModelMat();
    void SetModelMat(float * mat);
    void SetInitScale(glm::vec3 scale);
    void Decompose();
};