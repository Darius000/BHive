#pragma once

#include "BHivePCH.h"

namespace BHive
{
	struct WindowProps
	{
		FString Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const FString& title = "BHive Engine", unsigned int width = 1280, unsigned int height = 720)
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

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		float GetAspectRatio() { return (float)GetWidth() / (float)GetHeight();};

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}