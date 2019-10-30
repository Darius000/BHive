#include "SandBox2D.h"

SandBox2D::SandBox2D()
	:Layer("SandBox2D") , m_OrthoCameraController(16.0f / 9.0f, true)
{
	
}

void SandBox2D::OnAttach()
{
	BHive::BString vertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec4 v_Position;
			out vec4 v_Color;
			out vec2 v_TexCoord;
			
			void main()
			{
				v_TexCoord = a_TexCoord;
				v_Color = a_Color;
				v_Position =  vec4(a_Position, 1.0);
				gl_Position =  u_ViewProjection * u_Model * vec4(a_Position, 1.0);
			}
			
		)";

	BHive::BString fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Position;
			in vec4 v_Color;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
			
		)";

	//shader = BHive::Shader::Create("Default", vertexSrc, fragmentSrc);
	shader = BHive::Shader::Create("Assets/Shaders/Default.glsl");
	//BHive::AssetManager::AddShader(shader);
	BHive::ShaderLibrary::Add(shader);

	m_Texture = BHive::Texture2D::Create("Assets/Textures/grass.png");

	BHive::Timer time2("Sandbox");

	BHive::Actor* actor0 = BHive::SpawnActor<BHive::Actor>("Actor 0", BHive::Transform(BHive::Vector3(0.0f, 0.0f,-.5f), BHive::Rotator(0.0f)));
	BHive::Plane* plane = actor0->AddComponent<BHive::Plane>();
	plane->SetShader(BHive::ShaderLibrary::Get("Default"));
	plane->SetTexture(m_Texture);
	//BHive::Entity* E0 = scene0->AddEntity<BHive::Entity>();

	//BHive::Ref<BHive::Entity> square = std::shared_ptr<BHive::Entity>(E0);

	//BHive::Plane* T1 = square->AddComponent<BHive::Plane>();
	//T1->SetShader(shader);
	//T1->SetTexture(m_Texture);

	//BHive::Renderer2D::AddScene(scene0);

	BHive::Renderer2D::Init();
}

void SandBox2D::OnUpdate(const BHive::Time& time)
{
	m_OrthoCameraController.OnUpdate(time);

	BHive::Renderer2D::Begin(m_OrthoCameraController.GetCamera());
	BHive::Renderer2D::End();
}

void SandBox2D::OnImGuiRender()
{
	BHive::BString ImGUIName = m_DebugName + " Settings";
	ImGui::Begin(*ImGUIName);
	ImGui::End();
}

void SandBox2D::OnEvent(BHive::Event& event)
{
	m_OrthoCameraController.OnEvent(event);
}

void SandBox2D::OnDetach()
{
	BHive::Renderer2D::ShutDown();
}

