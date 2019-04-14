#pragma once

#include "Assets/Texture2D.h"
#include "RenderComponent.h"
#include "Cameras/Camera.h"

namespace BHive
{
	class BHive_API BillboardComponent : public RenderComponent
	{
	public:
		BillboardComponent();
		virtual ~BillboardComponent();

		virtual void ComponentStart() override;
		virtual void ComponentUpdate(float DeltaTime) override;
		virtual void Render() override;
		virtual void Construct() override;
		void SetTexture(std::string fileName, std::string path);
		void SetTexture(Texture2D* InTexture);
		/*
			0 = Opaque
			1 = CutOut
			2 = Transparent
		*/
		void SetBlendMode(int InMode);
		void SetSize(float InSize);
		void SetColor(glm::vec4 InColor);

	protected:
		float size;
		glm::vec4 color;
		Texture2D* texture;
		int blendMode;

	private:
		float CameraDistance(Camera* camera);
	};
}
