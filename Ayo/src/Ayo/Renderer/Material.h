#pragma once

namespace Ayo
{

    class Shader;

    class Material
    {
    public:

        void SetupShader(const std::shared_ptr<Shader>& shader);

        virtual void SetBaseColor(Vector3 color) = 0;

    protected:
        virtual void SetShaderProperties(const std::shared_ptr<Shader>& shader) = 0;

    };

}

