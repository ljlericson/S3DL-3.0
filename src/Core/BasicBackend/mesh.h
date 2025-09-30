#pragma once
#include <vector>
#include <memory>

#include "shader.h"
#include "Camera.h"

namespace Core
{
	namespace BasicBackend
	{
		// heavily 
		class BasicMesh
		{
		public:
			virtual ~BasicMesh() = default;

			void draw(BasicShader* shader, BasicCamera* camera) const;
		};
	}
} 