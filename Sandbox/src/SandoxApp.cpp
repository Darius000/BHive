#include <BHive.h>
#include "SandBox2D.h"
#include "BHive/Core/EntryPoint.h"

class ExampleLayer : public BHive::Layer 
{
public:
	ExampleLayer()
		:Layer("Example"),m_OrthoCameraController(16.0f/ 9.0f, true), E0(nullptr), T0(nullptr)
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

			uniform vec3 u_Color;
			uniform sampler2D u_Texture;

			void main()
			{
				//color = vec4(v_Position.xyz, 1.0);
				//color = v_Color;
				//color = vec4(v_TexCoord, 0.0, 1.0);
				//color = vec4(u_Color, 1.0);
				color = texture(u_Texture, v_TexCoord) * vec4(u_Color, 1.0);
			}
			
		)";

		shader = BHive::Ref<BHive::Shader>(BHive::Shader::Create("Default",vertexSrc, fragmentSrc));
		//shader = BHive::Ref<BHive::Shader>(BHive::Shader::Create("Assets/Shaders/Default.glsl"));
		BHive::AssetManager::AddShader(shader);

		m_Texture = BHive::Texture2D::Create("Assets/Textures/grass.png");
		m_Texture2 = BHive::Texture2D::Create("Assets/Textures/container.jpg");

		//shader->Bind();
		//std::dynamic_pointer_cast<BHive::OpenGLShader>(shader)->SetInt("u_Texture", 0);

		//Load textures in folder BHive::TextureManager::Load("Resources") in Application;
		//BHive::TextureManager::Import("Resources/tex0.png");
		//BHive::Material* material = BHive::MaterialManager::CreateMaterial(shader, "Name");
		//BHive::MaterialInstance* materialInstance = BHive::MaterialManager::CreateInstance(material, "I_Name");
		//BHive::Texture2D* texture = BHive::TextureManager::Get("tex0.png");

		//materialInstance->SetValue("u_Color", BHive::Color(255, 125, 0, 255));
		//materialInstance->SetTexture("u_AlbedoMap", texture);

		//m_Texture->Bind();

		BHive::Ref<BHive::Scene> scene0 = std::make_shared<BHive::Scene>(m_OrthoCameraController.GetCamera());

		E0 = scene0->AddEntity<BHive::Entity>();
		E0->GetTransform().SetScale(2.5f);

		T0 = E0->AddComponent<BHive::Triangle>(.25f, .5f);
		T0->SetShader(shader);
		T0->SetTexture(m_Texture2);

		BHive::Plane* T1 = E0->AddComponent<BHive::Plane>();
		T1->SetShader(shader);
		T1->SetTexture(m_Texture);

		T0->AddChild(*T1);

		BHive::Renderer::AddScene(scene0);
		BHive::Renderer::BeginScene(0);
	}

public:
	virtual void OnUpdate(const BHive::Time& time) override
	{
		BHive::RenderCommands::SetClearColor(BHive::Color(50,50, 50, 255));
		BHive::RenderCommands::Clear();

		m_OrthoCameraController.OnUpdate(time);

		dynamic_cast<BHive::OpenGLShader*>(T0->GetShader())->SetVector3("u_Color", glm::vec3(color.r, color.g, color.b));

		BHive::Renderer::UpdateScene(time);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", *color);
		ImGui::End();
	}

	virtual void OnEvent(BHive::Event& event) override
	{
		m_OrthoCameraController.OnEvent(event);
	}

	private:
		BHive::Entity* E0;
		BHive::Triangle* T0;
		BHive::Entity* Camera;
		BHive::OrthographicCameraController m_OrthoCameraController;
		float cameraSpeed = .01f;
		float rotationZ = 0.0f;
		BHive::FVector3 m_CameraPosition;
		BHive::Ref<BHive::Shader> shader;
		BHive::LinearColor color;
		BHive::Ref<BHive::Texture2D> m_Texture;
		BHive::Ref<BHive::Texture2D> m_Texture2;
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());	
		PushLayer(new SandBox2D());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}