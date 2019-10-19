#include "BHivePCH.h"
#include "RenderCommands.h"
#include "BHive/Platforms/Opengl/OpenGLRendererAPI.h"

namespace BHive
{
	RendererAPI* RenderCommands::s_RendererAPI = new OpenGLRendererAPI;
}