#pragma once
namespace data {
    static float topRightCanvasVertices[] =  {
        1.0f, 1.0f, 0.0f,  .0f, .0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,  .0f, .0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f,  .0f, .0f, 1.0f, 0.0f, 1.0f,
        0.5f, 1.0f, 0.0f,  .0f, .0f, 1.0f, 0.0f, 0.0f,
    };

    static float quarterCanvasVertices[] =  {
        1.0f, 1.0f, 0.0f,  .0f, .0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  .0f, .0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  .0f, .0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  .0f, .0f, 1.0f, 0.0f, 0.0f,
    };

    static float fullScreenCanvasVertices[] = {
        1.0f, 1.0f, 0.0f, .0f, .0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, .0f, .0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, .0f, .0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, .0f, .0f, 1.0f, 0.0f, 0.0f,
    };

    static int canvasIndices[] = {
        0, 1, 2,
        0, 2, 3,
    };
};