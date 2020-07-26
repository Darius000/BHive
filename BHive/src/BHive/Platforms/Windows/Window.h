#pragma once

#include "BHivePCH.h"
#include "BHive/Renderer/Texture.h"

namespace BHive
{
	struct WindowProps
	{
		BName Title;
		uint32 Width;
		uint32 Height;

		WindowProps(const BName& title = "BHive Engine", uint32 width = 1280, uint32 height = 720)
			:Title(title), Width(width), Height(height)
		{

		}
	};

	class BHive_API Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		float GetAspectRatio() { return (float)GetWidth() / (float)GetHeight();};

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetIcon(Ref<Texture2D> icon) = 0;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}