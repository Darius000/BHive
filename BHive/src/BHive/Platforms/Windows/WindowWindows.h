#pragma once

#include "BHive/Platforms/Windows/Window.h"
#include "BHive/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace BHive
{
	class WindowWindows : public Window
	{
	public:
		WindowWindows(const WindowProps& props);
		virtual ~WindowWindows();

		void OnUpdate() override;

		inline uint32 GetWidth() const override { return m_Data.Width;  };
		inline uint32 GetHeight() const override { return m_Data.Height; };

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void SetIcon(Ref<Texture2D> icon) override;
		void SetWindowHints();

		inline virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;
		GLFWimage* m_IconImage;

		struct WindowData
		{
			BName Title;
			uint32 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}