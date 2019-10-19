#include "SandBox2D.h"

SandBox2D::SandBox2D()
	:Layer("SandBox2D"), m_OrthoCameraController(16.0f / 9.0f, true)
{

}

void SandBox2D::OnAttach()
{
	BHive::FString vertexSrc = R"(
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

	BHive::FString fragmentSrc = R"(
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

	shader = BHive::Ref<BHive::Shader>(BHive::Shader::Create("Default", vertexSrc, fragmentSrc));
	//shader = BHive::Ref<BHive::Shader>(BHive::Shader::Create("Assets/Shaders/Default.glsl"));
	BHive::AssetManager::AddShader(shader);

	m_Texture = BHive::Texture2D::Create("Assets/Textures/grass.png");

	BHive::Ref<BHive::Scene> scene0 = std::make_shared<BHive::Scene>(m_OrthoCameraController.GetCamera());

	BHive::Ref<BHive::Entity> square = std::make_shared<BHive::Entity>(scene0->AddEntity<BHive::Entity>());

	BHive::Plane* T1 = square->AddComponent<BHive::Plane>();
	T1->SetShader(shader);
	T1->SetTexture(m_Texture);

	BHive::Renderer::AddScene(scene0);
	BHive::Renderer::BeginScene(0);
}

void SandBox2D::OnUpdate(const BHive::Time& time)
{
	BHive::RenderCommands::SetClearColor(BHive::Color(50, 50, 50, 255));
	BHive::RenderCommands::Clear();

	m_OrthoCameraController.OnUpdate(time);

	BHive::Renderer::UpdateScene(time);
}

void SandBox2D::OnImGuiRender()
{
	BHive::FString ImGUIName = m_DebugName + "Settings";
	ImGui::Begin(*ImGUIName);
	ImGui::End();
}

void SandBox2D::OnEvent(BHive::Event& event)
{
	m_OrthoCameraController.OnEvent(event);
}

void SandBox2D::OnDetach()
{
	
}

