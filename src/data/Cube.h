#pragma once
#include <functional>
#include <vector>
namespace data
{
    static float UnitHalfSquareVertices[] = {
        0.5, 0.5, 0,   0, 0, 0, 0, 0,
        0.5, -0.5, 0,  0, 0, 0, 0, 0,
        -0.5, -0.5, 0, 0, 0, 0, 0, 0,
        -0.5, 0.5, 0,  0, 0, 0, 0, 0,
    };
    static int UnitHalfSquareIndices[] = {
        0, 1, 2, 0, 2, 3
    };

    static float UnitHalfCubeVertices[] = {
        -0.5f,  0.5f, 0.5f,   
        0.5f,   0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f,  -0.5f, 0.5f,
        -0.5f, 0.5f,  -0.5f,
        0.5f,  0.5f,  -0.5f,
        -0.5f, -0.5f, -0.5f, 
        0.5f,  -0.5f, -0.5f,
    };

    static float UnitCubeVertices[] = {
        -1.0f,  1.0f, 1.0f,     
        1.0f,   1.0f, 1.0f,     
        -1.0f, -1.0f, 1.0f,     
        1.0f,  -1.0f, 1.0f,     
        -1.0f, 1.0f,  -1.0f,    
        1.0f,  1.0f,  -1.0f,
        -1.0f, -1.0f, -1.0f, 
        1.0f,  -1.0f, -1.0f,
    };

    static float UnitCubeNormals[] = {
        .0f, 0.0f, 1.0f,

        .0f, 0.0f, -1.0f,

        -1.0f, .0f, .0f,

        1.0f, .0f, .0f,

        .0f, 1.0f, .0f,

        .0f, -1.0f, .0f,
    };



    static int UnitCubeIndices[] = {
        0, 1, 2,
        1, 2, 3,  // front

        4, 5, 6,
        5, 6, 7,  // back

        0, 2, 6, 
        0, 4, 6,  // left

        1, 3, 5, 
        3, 7, 5,  // right

        0, 1, 5, 
        0, 4, 5,  // top

        2, 3, 7, 
        2, 6, 7,  // bottom
    };

    static float UnitCubeUVs[] = {
        0.0f, 0.0f,     1.0f, 0.0f,         0.0f, 1.0f,         
        1.0f, 0.0f,     0.0f, 1.0f,         1.0f, 1.0f,

        0.0f, 0.0f,     1.0f, 0.0f,         0.0f, 1.0f,         
        1.0f, 0.0f,     0.0f, 1.0f,         1.0f, 1.0f,

        1.0f, 0.0f,     1.0f, 1.0f,         0.0f, 1.0f,         
        1.0f, 0.0f,     0.0f, 0.0f,         0.0f, 1.0f,

        0.0f, 0.0f,     0.0f, 1.0f,         1.0f, 0.0f,         
        0.0f, 1.0f,     1.0f, 1.0f,         1.0f, 0.0f,

        0.0f, 1.0f,     1.0f, 1.0f,         1.0f, 0.0f,         
        0.0f, 1.0f,     0.0f, 0.0f,         1.0f, 0.0f,

        0.0f, 0.0f,     1.0f, 0.0f,         1.0f, 1.0f,
        0.0f, 0.0f,     0.0f, 1.0f,         1.0f, 1.0f,
    };

    static glm::vec3 GetVerticesByIndex(int index)
    {
        return glm::vec3(UnitCubeVertices[index * 3], UnitCubeVertices[index * 3 + 1], UnitCubeVertices[index * 3 + 2]);
    }
    
    static glm::vec2 GetUVByIndex(int index)
    {
        return glm::vec2(UnitCubeUVs[index*2], UnitCubeUVs[index*2 + 1]);
    }

    static glm::vec3 GetNormalByIndex(int index)
    {
        int target_index = index * 3;
        return glm::vec3(UnitCubeNormals[target_index], UnitCubeNormals[target_index + 1], UnitCubeNormals[target_index + 2]);
    }

    static std::vector<float> GetCubeVertices()
    {
        std::vector<float> result;
        for (int i = 0; i < 12 * 3 ; i++)
        {
            glm::vec3 vertices = GetVerticesByIndex(UnitCubeIndices[i]);
            glm::vec2 uv = GetUVByIndex(i);
            int normalIndex = i / 6;
            glm::vec3 normals  = glm::vec3(UnitCubeNormals[normalIndex * 3], UnitCubeNormals[normalIndex * 3 + 1], UnitCubeNormals[normalIndex * 3 + 2]);

            result.push_back(vertices.x);
            result.push_back(vertices.y);
            result.push_back(vertices.z);

            result.push_back(normals.x);
            result.push_back(normals.y);
            result.push_back(normals.z);

            result.push_back(uv.x);
            result.push_back(uv.y);
           

        }

        return result;

    }



};