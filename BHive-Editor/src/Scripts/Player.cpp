#include "BHivePCH.h"
#include "Player.h"

namespace BHive
{

	void Player::OnCreate()
	{
		GetComponent<DirectionalLightComponent>().m_LightBrightness = 0.0f;
	}

	void Player::OnUpdate(const Time& time)
	{
		GetComponent<DirectionalLightComponent>().m_LightBrightness += .001f;
	}

}