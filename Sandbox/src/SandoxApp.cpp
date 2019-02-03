#include <BHive.h>

class ExampleLayer : public BHive::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		BH_INFO("ExampleLayer::Update");
	}

	void OnEvent(BHive::Event& event) override
	{
		BH_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new BHive::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}