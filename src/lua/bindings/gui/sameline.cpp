#pragma once
#include "common.hpp"

#include "sameline.hpp"

namespace lua::gui
{
	void sameline::draw()
	{
		ImGui::SameLine();
	}
}