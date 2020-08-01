#pragma once

#include <BHive.h>

class SandBox2D : public BHive::Layer
{
public:
	SandBox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(const BHive::Time& time) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(BHive::Event& event) override;

private:

};