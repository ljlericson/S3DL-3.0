#include "../BasicBackend/shader.h"
#include "../../Vender/Metal/Metal/Metal.hpp"

namespace Core
{
    namespace MetalBackend
    {
        class Shader : public BasicBackend::BasicShader
        {
        public:
            Shader();

            ~Shader();

            void use() const override;
            
            void unuse() const override;
        };
    }
}
