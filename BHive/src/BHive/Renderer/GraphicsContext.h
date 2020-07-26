#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H


namespace BHive
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext(){}
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif