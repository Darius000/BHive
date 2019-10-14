#ifndef RENDERER_H
#define RENDERER_H

namespace BHive
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; };
		void SetAPI(RendererAPI API);
	private:
		static RendererAPI s_RendererAPI;
	};
	
}

#endif