#include "Editor.h"
#include "Scene.h"
#include "Components/CameraComponent.h"

namespace nc
{
	void Editor::Update()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent)) m_active = !m_active; // ` key
	}

	void Editor::ProcessGui(Scene* scene)
	{
		if (!m_active) return;

		// show resources
		// resource type dropdown
		ImGui::Begin("resources");
		const char* resourceTypes[] = { "Texture", "Model", "Material", "All" };
		ImGui::Combo("Filter", reinterpret_cast<int*>(&m_currentResourceType), resourceTypes, IM_ARRAYSIZE(resourceTypes));

		auto resources = GET_RESOURCES(Resource);
		for (auto& resource : resources) {
			bool shouldDisplay = false;

			switch (m_currentResourceType) {
			case TYPE_TEXTURE:
				shouldDisplay = std::dynamic_pointer_cast<Texture>(resource) != nullptr;
				break;
			case TYPE_MODEL:
				shouldDisplay = std::dynamic_pointer_cast<Model>(resource) != nullptr;
				break;
			case TYPE_MATERIAL:
				shouldDisplay = std::dynamic_pointer_cast<Material>(resource) != nullptr;
				break;
			case ALL:
			default:
				shouldDisplay = true;
				break;
			}

			if (shouldDisplay) {
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected)) {
					m_selected = resource.get();
				}
			}
		}
		ImGui::End();


		// show scene
		ImGui::Begin("Scene");
		scene->ProcessGui();
		ImGui::Separator();

		// show actors
		ImGui::BeginChild("Actors");
		// actor controls
		if (ImGui::BeginPopupContextWindow())
		{
			auto cameras = scene->GetComponents<CameraComponent>();
			auto camera = (!cameras.empty()) ? cameras[0] : nullptr;

			if (ImGui::MenuItem("Create Empty")) 
			{
				auto actor = CREATE_CLASS(Actor);
				actor->name = StringUtils::CreateUnique(actor->GetClassName()); 
				actor->Initialize(); 
				m_selected = actor.get(); 
				scene->Add(std::move(actor)); 
			}
			if (ImGui::MenuItem("Sphere")) 
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Sphere");
				actor->name = StringUtils::CreateUnique(actor->name); 
				if (camera)
				{
					//spawns actor in front of camera
					actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				} 
				actor->Initialize();  
				m_selected = actor.get();  
				scene->Add(std::move(actor));  
			} 

			if (ImGui::MenuItem("Cube"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Cube");
				actor->name = StringUtils::CreateUnique(actor->name);  
				actor->Initialize(); 
				if (camera)
				{
					//spawns actor in front of camera
					actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f; 
				}
				m_selected = actor.get();  
				scene->Add(std::move(actor));  
			}
			if (ImGui::MenuItem("Camera")) 
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Camera");
				actor->name = StringUtils::CreateUnique(actor->name); 
				actor->Initialize(); 
				if (camera)
				{
					//spawns actor in front of camera
					actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f; 
				}
				m_selected = actor.get(); 
				scene->Add(std::move(actor)); 
			}
			if (ImGui::MenuItem("Light")) 
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Light");
				actor->name = StringUtils::CreateUnique(actor->name); 
				actor->Initialize(); if (camera)
				{
					//spawns actor in front of camera
					actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f; 
				}
				m_selected = actor.get(); 
				scene->Add(std::move(actor)); 
			}

			ImGui::EndPopup();
		}

		for (auto& actor : scene->m_actors)
		{
			if (ImGui::Selectable(actor->name.c_str(), actor.get() == m_selected))
			{
				m_selected = actor.get();
			}
		}
		ImGui::EndChild();
		ImGui::End();

		// show inspector
		ImGui::Begin("Inspector");
		if (m_selected)
		{
			m_selected->ProcessGui();
			// delete selected actor
			if (ImGui::IsKeyPressed(ImGuiKey_Delete))
			{
				auto actor = dynamic_cast<Actor*>(m_selected);
				if (actor)
				{
					scene->Remove(actor);
					m_selected = nullptr;
				}
			}
		}
		ImGui::End();

	}
}