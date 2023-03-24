 // check if pause is on

//calculate button position (current position + camera position)
//unzoom the screen
//turn on collision
//turn set sprites

/*!*************************************************************************
****
\file PauseMenu.cpp
\author Lau Yong Hui
\par DP email:l.yonghui.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM250
\date 20/01/2023
\brief	Script That allow buttons to work when selected and clicked on

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#include "empch.h"
#include "PauseMenu.h"
#include "../ECS/SceneManager.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/Graphics/Graphics.h"
#include "Platform/LevelEditor/LevelEditor.h"

namespace EM
{
	void PauseMenu::Start()
	{
	}

	void PauseMenu::Update(float Frametime)
	{
		
		UNREFERENCED_PARAMETER(Frametime);
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& ID_tag = p_ecs.GetComponent<Tag>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		auto& spt = p_ecs.GetComponent<Sprite>(GetScriptEntityID());

		vec2D camPos = vec2D(Graphic::mcamera->GetPosition().x, Graphic::mcamera->GetPosition().y);
		
		if (p_Input->KeyPressed(GLFW_KEY_ESCAPE)&&p_GUI->check_pause()==false)
		{
			if (ID_tag.GetTag() == "PauseMenuBG")
			{
			p_GUI->toggle_pause();
			Graphic::mcamera->SetZoomLevel(1.0f);
			Graphic::camera.SetPosition({ 0.0f, -4.0f, 0.0f });
			}
			
		}

		if (p_GUI->check_pause() == true&& p_Editor->is_ShowWindow == false)
		{
			if (ID_tag.GetTag() == "Resume")
			{
				spt.SetTexture("Resume_Idle");
			}
			if (ID_tag.GetTag() == "Quit")
			{
				spt.SetTexture("QG_Y");
			}
			if (ID_tag.GetTag() == "Options")
			{
				spt.SetTexture("Options_Idle");
			}
			if (ID_tag.GetTag() == "Restart")
			{
				spt.SetTexture("Restart_Idle");//to be change
			}
			if (ID_tag.GetTag() == "PauseMenuBG")
			{
				spt.SetTexture("MenuPanel");//to be change
			}
			if (curr_state != button_state::click)
				curr_state = button_state::idle;

			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::idle)
			{
				curr_state = button_state::click;
			}
			else if (p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::click)
			{
				curr_state = button_state::release;
			}
			glm::vec2 newmousepos{ (p_GUI->MousePosition.x + camPos.x),(p_GUI->MousePosition.y + camPos.y)};
			//component to detect if mouse is hovering over the buttons
			if (is_within_box(newmousepos, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
			{
				if (ID_tag.GetTag() == "Resume" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
				{
					spt.SetTexture("Resume_Hover");
				}
				if (ID_tag.GetTag() == "Quit" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
				{
					spt.SetTexture("QG_B");
				}
				if (ID_tag.GetTag() == "Restart" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
				{
					spt.SetTexture("Restart_Hover"); //to be updated
				}
				if (curr_state == button_state::release)
				{
					if (ID_tag.GetTag() == "Resume")
					{
						p_GUI->toggle_pause();
						Graphic::camera.SetPosition(p_GUI->PrevCamPos);
						Graphic::mcamera->SetZoomLevel(0.25f);
					}
					if (ID_tag.GetTag() == "Quit")
					{
						p_GUI->toggle_pause();
						p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
					}
					if (ID_tag.GetTag() == "Restart")
					{
						p_GUI->toggle_pause();
						Graphic::camera.SetPosition(p_GUI->PrevCamPos);
						Graphic::mcamera->SetZoomLevel(0.25f);
						p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
					}
				}
				if (curr_state == button_state::click)
				{
					if (ID_tag.GetTag() == "Resume")
					{
						spt.SetTexture("Resume_Click");
					}
					if (ID_tag.GetTag() == "Quit")
					{
						spt.SetTexture("QG_R");
					}
					if (ID_tag.GetTag() == "Restart")
					{
						spt.SetTexture("Restart_Click");
					}
				}
			}			
		}
		else if (p_GUI->check_pause() == false)
		{
			spt.SetTexture("Blank");
		}
	}

	void PauseMenu::End()
	{
		delete this;
	}

	PauseMenu* PauseMenu::Clone() const
	{
		return new PauseMenu(*this);
	}

	std::string PauseMenu::GetScriptName()
	{
		return "PauseMenu";
	}

	bool PauseMenu::is_within_box(glm::vec2 cur, Collider box, Transform trans)
	{
		if (cur.x > ((box[0].mMin.x * (trans.GetScale().x/2 )) + trans.GetPos().x) && cur.y > (box[0].mMin.y * (trans.GetScale().y / 2) + trans.GetPos().y) &&
			cur.x < ((box[0].mMax.x * (trans.GetScale().x/2 )) + trans.GetPos().x) && cur.y < (box[0].mMax.y * (trans.GetScale().y / 2) + trans.GetPos().y))
		{
			return true;//return true if the position of the cursor is between both of the button minimun and maximum bounding point
		}
		else
			return false;// return false if it isnt
	}
}