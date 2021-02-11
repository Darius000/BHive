#pragma once

//for use by BHive applications

#include "BHive/BHivePCH.h"
#include "imgui.h"
#include "BHive/ImGui/ImGuiWrappers.h"
#include "BHive/Layers/ImGuiLayer.h"
#include "Bhive/Object/Camera.h"
#include "BHive/Components/Component.h"
#include "BHive/Managers/AssetManagers.h"

//-------Renderer----------------

#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/Renderer2D.h"
#include "BHive/Renderer/Shader.h"
#include "BHive/Renderer/Framebuffer.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"


//----------Models-------------------
#include "BHive/Renderer/Model/Mesh.h"

//---------Models with predefined meshes
#include "BHive/Renderer/Model/Plane.h"
#include "BHive/Renderer/Model/Triangle.h"
#include "BHive/Renderer/Model/Quad.h"
