#pragma once
#include <vector>
#include <glm.hpp>
#include "renderer/OGLRenderData.h"

class Model {
public:
    void init();

    OGLMesh getVertexData();

private:
    OGLMesh mVertexData;
};
