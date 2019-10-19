#pragma once

//for use by BHive applications

#include "BHive/BHivePCH.h"
//#include "BHive/Core/Application.h"
//#include "BHive/Core/Layer.h"
//#include "BHive/Core/Log.h"
//
//#include "BHive/Core/Input.h"
//#include "BHive/Core/KeyCodes.h"
//#include "BHive/Core/MouseCodes.h"
//
//#include "BHive/Core/Time.h"
//
//#include "BHive/Math/MathLibrary.h"

#include "imgui.h"
#include "BHive/ImGui/ImGuiLayer.h"
#include "BHive/Object/Entity.h"
#include "BHive/Shapes/Triangle.h"
#include "BHive/Shapes/Plane.h"
#include "BHive/Scene/Scene.h"
#include "BHive/AssetManagement/AssetManager.h"
#include "BHive/Components/CameraComponents.h"
#include "BHive/Controllers/OrthographicCameraController.h"

//-------Renderer----------------

#include "BHive/Renderer/Renderer.h"
#include "BHive/Renderer/Shader.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"
