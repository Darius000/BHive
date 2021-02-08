#include "IProperty.h"


void Reflection::IProperty::OnImGuiRender()
{

	OnImGuiBegin();
	OnImGuiDraw();
	OnImGuiEnd();
}
