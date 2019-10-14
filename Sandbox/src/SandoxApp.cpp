#include <BHive.h>

#include "imgui/imgui.h"
#include "BHive/Entities/Entity.h"
#include "BHive/Components/Primitives/Triangle.h"
#include "BHive/Components/Primitives/Plane.h"
#include "BHive/Levels/World.h"
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
		BHive::Entity* E0 = AddEntity<BHive::Entity>();
		//E0->GetTransform().SetPosition(-.5f, 0.0f, 0.0f);

		BHive::Triangle* T0 = E0->AddComponent<BHive::Triangle>();
		BHive::Plane* T1 = E0->AddComponent<BHive::Plane>();
		T0->AddChild(*T1);
		
		T0->SetHeight(.5f);
		T0->SetWidth(.5f);
		//T0->SetRelativeLocation(BHive::Vector3(0.0f, 0.0f, 0.0f));

		T1->SetHeight(.25f);
		T1->SetWidth(.25f);
		//T1->SetRelativeLocation(BHive::Vector3(.25f, -.25f, 0.0f));
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