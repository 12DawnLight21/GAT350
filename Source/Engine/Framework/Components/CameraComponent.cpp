#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace nc
{
	CLASS_DEFINITION(CameraComponent)

	bool CameraComponent::Initialize()
	{
		// get aspect from window if not set
		if (aspect == 0)
		{
			// set aspect with renderer width / renderer height (make sure it is a floating point division)
			// aspect = width / height;
			aspect = static_cast<float>(ENGINE.GetSystem<Renderer>()->GetWidth()) / static_cast<float>(ENGINE.GetSystem<Renderer>()->GetHeight());
		}

		return true;
	}

	void CameraComponent::Update(float dt)
	{
		view = glm::lookAt(m_owner->transform.position, (m_owner->transform.position + m_owner->transform.Forward()), m_owner->transform.Up());
		
		if (projectionType == Perspective)
		{
			projection = glm::perspective(glm::radians(fov), aspect, near, far); //converts fov to rads
		}
		else
		{
			projection = glm::ortho(-size * aspect * 0.5f, size * aspect * 0.5f, -size * aspect * 0.5f, size * aspect * 0.5f, near, far);
		}

	}

	void CameraComponent::SetPerspective(float fov, float aspect, float near, float far)
	{
		// set this class fov, aspect, near and far values with parameters (this->fov = fov, ...)
		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		// set projection matrix with glm::perspective function (fov is in degrees, convert to radians)
		// projection = glm::perspective(<parameters>);
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void CameraComponent::SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		// set view matrix with glm::lookAt function
		// view = glm::lookAt(<parameters>)
		view = glm::lookAt(eye, center, up);
	}

	void CameraComponent::SetProgram(res_t<Program> program)
	{
		// set program uniform for "view" with view matrix
		program->SetUniform("view", view);
		// set program uniform for "projection" with projection matrix
		program->SetUniform("projection", projection);
	}

	void CameraComponent::ProcessGui()
	{
		// use ImGui::DragFloat to set fov, aspect, near and far values (use speed of 0.1f)
		//ImGui::Begin("Camera");

		const char* types[] = { "Perspective", "Orthographic" };
		ImGui::Combo("Projection", (int*)(&projectionType), types, 2);

		//mins n maxes might need changed
		ImGui::DragFloat("Field of View (FOV)", &fov, 0.1f, 0.1f, 179.9f);
		ImGui::DragFloat("Aspect", &aspect, 0.1f, 1, 90);
		ImGui::DragFloat("Near", &near, 0.1f, 0, 1);
		ImGui::DragFloat("Far", &far, 0.1f, 0, 100);
		ImGui::DragFloat("Size", &size, 0.1f, 0, 12);
		
		
		//ImGui::End();

	}

	void CameraComponent::Read(const json_t& value)
	{
		// READ_DATA of fov, aspect, near and far values
		READ_DATA(value, fov); 
		READ_DATA(value, aspect);
		READ_DATA(value, near);
		READ_DATA(value, far);

		std::string projectionTypeName;
		READ_NAME_DATA(value, "projectionType", projectionTypeName);
		if (StringUtils::IsEqualIgnoreCase("orthograhpic", projectionTypeName)) projectionType = Orthographic;

		READ_DATA(value, size);
	}
}