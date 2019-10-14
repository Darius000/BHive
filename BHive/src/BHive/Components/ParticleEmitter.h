#pragma once

#include "BillboardComponent.h"

namespace BHive
{
	class BHive_API Particle : public BillboardComponent
	{
		BCLASS(Particle, ComponentCategory, BillboardComponent)

	public:
		Particle();
		~Particle();

		virtual void ComponentUpdate(float DeltaTime) override;
		void UpdatePosition(float deltaTime);
		//void UpdateColor(float deltaTime);

		float life;
		Vector3 velocity;
	};

	class BHive_API ParticleEmitter : public Component
	{

		BCLASS(ParticleEmitter, ComponentCategory, Component)

	public:
		ParticleEmitter();
		~ParticleEmitter();

		/*virtual void ComponentStart() override;
		virtual void ComponentUpdate(float deltaTime) override;

		void SetNumberParticles(unsigned int num);
		void SpawnParticle();
		void SetParticleTexture(Texture2D* particleTexture);
		void SetParticleColor(glm::vec4 particleColor);
		void SetParticleShader(Shader* inShader);

		std::vector<Particle*> particles;

	protected:
		Texture2D* texture;
		glm::vec4 color;

	private:
		unsigned int lastUsedParticle;*/
	};
}
