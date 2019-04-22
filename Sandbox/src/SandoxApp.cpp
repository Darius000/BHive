#include <BHive.h>

#include "imgui/imgui.h"
#include "GameObject.h"
#include "World.h"
#include "Components/BillboardComponent.h"

class ExampleLayer : public BHive::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
		
	}

	void OnAttach() override
	{
	}

	void OnUpdate() override
	{
		if (BHive::Input::IsKeyPressed(BH_KEY_TAB))
			BH_INFO("Tab key is pressed(POLL");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Example");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(BHive::Event& event) override
	{
		if (event.GetEventType() == BHive::EventType::KeyPressed)
		
		{
			BHive::KeyPressedEvent& e = (BHive::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BH_KEY_TAB)
				BH_INFO("Tab key is pressed(Event)");
			BH_TRACE("{0}", (char)e.GetKeyCode());
			//BH_TRACE("{0}", event.ToString());
		}
	}
};

class WorldOne : public BHive::World
{

public:
	virtual void CreateWorld() override
	{
		BH_INFO("Created World 1");
		/*BHive::Camera* MainCam = AddEntity<BHive::Camera>();
		BHive::GameObject* Box = AddEntity<BHive::GameObject>();
		Box->AddComponent<BHive::BillboardComponent>();*/
	}
};

class Sandbox : public BHive::Application
{
public:
	Sandbox()
	{
		WorldOne* w = new WorldOne();
		w->SetActive();
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

BHive::Application* BHive::CreateApplication()
{
	return new Sandbox();
}