#pragma once

extern ImFont* ico;
extern ImFont* ico_combo;
extern ImFont* ico_button;
extern ImFont* ico_grande;
extern ImFont* segu;
extern ImFont* default_segu;
extern ImFont* bold_segu;

extern float color_edit4[4];
extern float accent_color[4];

extern int tab_count;
extern int ui_tabs;
extern float size_child;

namespace big
{
	void ui_main();
	void help_marker(const char* text);
}