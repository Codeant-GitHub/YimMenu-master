#pragma once
#include "common.hpp"

#include "separator.hpp"

namespace lua::gui
{
	void separator::draw()
	{
		ImGui::Separator();
	}
}