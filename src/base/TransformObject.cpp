#include "TransformObject.h"

void TransformObject::Translate(glm::vec3 trans)
{
     m_Position = trans;
     CalcModelMat();
}

void TransformObject::RotateRadians(glm::vec3 axisAndAngles)
{
    float angleX = axisAndAngles.x;
    float angleY = axisAndAngles.y;
    float angleZ = axisAndAngles.z;

    glm::quat x = glm::angleAxis((angleX), glm::vec3(1, 0, 0));
    glm::quat y = glm::angleAxis((angleY), glm::vec3(0, 1, 0));
    glm::quat z = glm::angleAxis((angleZ), glm::vec3(0, 0, 1));

    glm::quat q = x * y * z;

    m_Rotate = q;
    CalcModelMat();
}
void TransformObject::Rotate(glm::vec3 axisAndAngles)
{
    float angleX = axisAndAngles.x;
    float angleY = axisAndAngles.y;
    float angleZ = axisAndAngles.z;

    glm::quat x = glm::angleAxis(glm::radians(angleX), glm::vec3(1, 0, 0));
    glm::quat y = glm::angleAxis(glm::radians(angleY), glm::vec3(0, 1, 0));
    glm::quat z = glm::angleAxis(glm::radians(angleZ), glm::vec3(0, 0, 1));

    glm::quat q = x * y * z;

    m_Rotate = q;
    CalcModelMat();
}
void TransformObject::Rotate(float angle, glm::vec3 axis)
{
    glm::quat q = glm::angleAxis(glm::radians(angle), axis);
    m_Rotate = q * m_Rotate;
    CalcModelMat();
}
void TransformObject::Rotate(glm::quat rot)
{
    m_Rotate = rot * m_Rotate;
    CalcModelMat();
}

void TransformObject::SetInitScale(glm::vec3 scale)
{
    m_InitScale = scale;
}

void TransformObject::SetPosition(glm::vec3 position)
{
    m_Position = position;
    CalcModelMat();
}

void TransformObject::Scale(glm::vec3 scale)
{
    m_Scale = scale;
    CalcModelMat();
}

void TransformObject::CalcModelMat()
{
   
    m_TransMat = glm::mat4(1.0);
    m_TransMat = glm::translate(m_TransMat, m_Position);
    m_Rotate = glm::angleAxis(0.01f, glm::vec3(0, 1, 0)) * m_Rotate;
    m_TransMat = glm::mat4_cast(m_Rotate) * m_TransMat;
    m_TransMat = glm::scale(m_TransMat, m_InitScale * m_Scale);

    //float angle = glm::length(m_Rotate) - 1;
    //glm::vec3 axis = glm::normalize(m_Rotate);
    
    
    //return {model, };
}

glm::mat4 & TransformObject::GetModelMat()
{
    return m_TransMat;
}

void TransformObject::SetModelMat(float * modelMat)
{
    m_TransMat = *((glm::mat4 *)modelMat);
    // decompose
    Decompose();
}

void TransformObject::Decompose()
{
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(m_TransMat, m_Scale, m_Rotate, m_Position, skew, perspective);
}


