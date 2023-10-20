#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc
{
	class World04 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		Transform m_transform;

		res_t<Material> m_material;
		res_t<Model> m_model;

		glm::vec3 m_ambientLight = glm::vec3(0.2, 0.2, 0.2);
		glm::vec3 m_diffuseLight = glm::vec3(1, 1, 1);
		glm::vec3 m_lightPosition = glm::vec3(0, 8, 0);
	};
}