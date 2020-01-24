#pragma once

namespace Ayo
{

    class Shader;

    class Material
    {
    public:

        void SetupShader(Shader& shader);

    protected:
        virtual void SetShaderProperties(Shader& shader) = 0;

    };

}

