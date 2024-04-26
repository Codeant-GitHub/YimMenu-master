
#include "common.hpp"
#include "ui_main.hpp"
#include "views/view.hpp"

#include "imgui.h"
#include "imgui_internal.h"

#pragma execution_character_set("utf-8")

//白泽，套壳 YimMenu 开源菜单的主界面调入

ImFont* ico          = nullptr;
ImFont* ico_combo    = nullptr;
ImFont* ico_button   = nullptr;
ImFont* ico_grande   = nullptr;
ImFont* segu         = nullptr;
ImFont* default_segu = nullptr;
ImFont* bold_segu    = nullptr;

float color_edit4[4]  = {1.00f, 1.00f, 1.00f, 1.000f};
float accent_color[4] = {0.745f, 0.151f, 0.151f, 1.000f};

int tab_count = 0;
int ui_tabs = 0;
float size_child = 0;

bool active = false;

namespace big
{
	void help_marker(const char* text)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(text);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	void ui_main()
	{
		{
			//    ImGuiWindowFlags_NoTitleBar: 不显示窗口的标题栏。
			//    ImGuiWindowFlags_NoResize : 禁止调整窗口大小。
			//    ImGuiWindowFlags_NoSavedSettings : 不保存窗口的设置（位置、大小等）。
			//    ImGuiWindowFlags_NoCollapse : 禁止窗口被折叠或最小化。
			//    ImGuiWindowFlags_NoScrollbar : 不显示窗口的滚动条。
			//    ImGuiWindowFlags_NoScrollWithMouse : 禁用鼠标滚轮滚动窗口内容。
			//    ImGuiWindowFlags_NoBackground : 窗口没有背景（透明）。

			DWORD window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground;

			{
				ImGui::SetNextWindowSize(ImVec2(905, 624));

				ImGui::Begin("Hola!", NULL, window_flags);
				{
					ImVec2 P1, P2;
					ImDrawList* pDrawList;
					const auto& p                   = ImGui::GetWindowPos();
					const auto& pWindowDrawList     = ImGui::GetWindowDrawList();
					const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();

					//DrawBackgroundBlur(pWindowDrawList, g_pd3dDevice);


					//if (scene == nullptr) D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &background, sizeof(background), 1920, 1080, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &scene);

					//ImGui::GetBackgroundDrawList()->AddImage(scene, ImVec2(0, 0), ImVec2(1920, 1080), ImVec2(0, 0), ImVec2(1, 1), ImColor(color_edit4[0], color_edit4[1], color_edit4[2], color_edit4[3]));

					pBackgroundDrawList->AddRectFilled(ImVec2(0.000f + p.x, 0.000f + p.y), ImVec2(905 + p.x, 624 + p.y), ImColor(35, 35, 35, 255), 10); // Background

					pWindowDrawList->AddRectFilled(ImVec2(189.000f + p.x, 75.000f + p.y), ImVec2(903 + p.x, 76 + p.y), ImColor(0, 0, 0, 255), 10); // bar line

					ImGui::SetCursorPos(ImVec2(800, 21));

					if (ImGui::OptButton("L", ImVec2(30, 30), false))
						;

					ImGui::SameLine(840);

					if (ImGui::OptButton("B", ImVec2(30, 30), true))
						;

					pWindowDrawList->AddRectFilled(ImVec2(0.000f + p.x, 0.000f + p.y), ImVec2(190 + p.x, 624 + p.y), ImGui::GetColorU32(ImGuiCol_ChildBg), 10, ImDrawFlags_RoundCornersLeft); // bar line

					const int vtx_idx_1 = pWindowDrawList->VtxBuffer.Size;

					//pWindowDrawList->AddText(ico_grande, 100.f, ImVec2(50.000f + p.x, 10.000f + p.y), ImColor(0.60f, 0.60f, 0.60f, 0.70f), "U");
					//名字默认高度是窗口顶部高度的20.0f
					//名字左边是窗口左边
					//原始线长100.0f
					pWindowDrawList->AddText(bold_segu, 60.0f, ImVec2(40.000f + p.x, 20.000f + p.y), ImColor(0, 0, 0, 255), "BaiZe");

					pWindowDrawList->AddRectFilled(ImVec2(40.000f + p.x, 75.000f + p.y), ImVec2(145 + p.x, 76 + p.y), ImColor(0.60f, 0.60f, 0.60f, 0.70f), 10); // bar line

					const int vtx_idx_2 = pWindowDrawList->VtxBuffer.Size;

					ImGui::ShadeVertsLinearColorGradientKeepAlpha(pWindowDrawList, vtx_idx_1, vtx_idx_2, ImVec2(0 + p.x, 0 + p.y), ImVec2(200 + p.x, 20 + p.y), ImColor(0.25f, 0.25f, 0.25f, 0.50f), ImColor(accent_color[0], accent_color[1], accent_color[2], accent_color[3]));

					ImGui::SetCursorPosY(110);

					if (ImGui::TabButton("F", "战局玩家", ImVec2(190, 40)) && tab_count != 0)
					{
						tab_count = 0;
						active    = true;
					}
					if (ImGui::TabButton("R", "自我选项", ImVec2(190, 40)) && tab_count != 1)
					{
						tab_count = 1;
						active    = true;
					}
					if (ImGui::TabButton("G", "载具选项", ImVec2(190, 40)) && tab_count != 2)
					{
						tab_count = 2;
						active    = true;
					}
					if (ImGui::TabButton("P", "武器选项", ImVec2(190, 40)) && tab_count != 3)
					{
						tab_count = 3;
						active    = true;
					}
					if (ImGui::TabButton("H", "世界选项", ImVec2(190, 40)) && tab_count != 4)
					{
						tab_count = 4;
						active    = true;
					}
					if (ImGui::TabButton("N", "网络事件", ImVec2(190, 40)) && tab_count != 5)
					{
						tab_count = 5;
						active    = true;
					}
					if (ImGui::TabButton("T", "恢复选项", ImVec2(190, 40)) && tab_count != 6)
					{
						tab_count = 6;
						active    = true;
					}
					if (ImGui::TabButton("J", "脚本插件", ImVec2(190, 40)) && tab_count != 7)
					{
						tab_count = 7;
						active    = true;
					}
					if (ImGui::TabButton("E", "菜单设置", ImVec2(190, 40)) && tab_count != 8)
					{
						tab_count = 8;
						active    = true;
					}
					if (active)
					{
						if (size_child <= 10)
							size_child += 1 / ImGui::GetIO().Framerate * 60.f;
						else
						{
							active  = false;
							ui_tabs = tab_count;
						};
					}
					else
					{
						if (size_child >= 0)
							size_child -= 1 / ImGui::GetIO().Framerate * 60.f;
					}

					pWindowDrawList->AddCircleFilled(ImVec2(57.000f + p.x, 570.000f + p.y), 25.000f, ImColor(10, 9, 10, 255), 30);

					pWindowDrawList->AddCircle(ImVec2(57.000f + p.x, 570.000f + p.y), 27.000f, ImColor(20, 19, 20, 255), 30, 4.000f);

					pWindowDrawList->AddText(segu, 40.f, ImVec2(51.000f + p.x, 548.000f + p.y), ImColor(0.60f, 0.60f, 0.60f, 0.50f), "?");


					const int vtx_idx_3 = pWindowDrawList->VtxBuffer.Size;

					pWindowDrawList->AddText(segu, 22.f, ImVec2(97.000f + p.x, 547.000f + p.y), ImColor(0.40f, 0.40f, 0.40f, 0.50f), "Benjy\nLifetime");

					const int vtx_idx_4 = pWindowDrawList->VtxBuffer.Size;

					ImGui::ShadeVertsLinearColorGradientKeepAlpha(pWindowDrawList, vtx_idx_3, vtx_idx_4, ImVec2(97.000f + p.x, 547.000f + p.y), ImVec2(200.000f + p.x, 567.000f + p.y), ImColor(0.35f, 0.35f, 0.35f, 0.50f), ImColor(0.90f, 0.90f, 0.90f, 1.00f));

					switch (ui_tabs)
					{
					case 0:

						ImGui::SetCursorPos(ImVec2(203, 88 - size_child));

						ImGui::BeginChild("Editor", ImVec2(339, 253), true);
						{
							static bool test_0 = false;
							ImGui::Checkbox("Checkbox_0", &test_0);

							static bool test_1 = false;
							ImGui::Checkbox("Checkbox_1", &test_1);

							static int slider_test_0 = 50;
							ImGui::SliderInt("Slider Intager", &slider_test_0, 1, 400);

							static float slider_test_1 = 0;
							ImGui::SliderFloat("Slider Float", &slider_test_1, 0.00f, 5.00f, "%.2f");
						}
						ImGui::EndChild();

						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));

						ImGui::BeginChild("Background", ImVec2(339, 210), true);
						{
							ImGui::ColorEdit4("Background Color", (float*)&color_edit4, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

							ImGui::ColorEdit4("Widget Color", (float*)&accent_color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						}
						ImGui::EndChild();

						ImGui::SetCursorPos(ImVec2(203, 353 - size_child));

						ImGui::BeginChild("Aimbot", ImVec2(339, 258), true);
						{
							static int selectedItem = 0;
							static const char* items[]{"Always", "Toggle"};
							ImGui::Combo("Aimbot Mode", &selectedItem, items, IM_ARRAYSIZE(items), 5);

							static char buf[64] = {""};
							ImGui::InputText("InputText", buf, 64);
						}
						ImGui::EndChild();


						ImGui::SetCursorPos(ImVec2(555, 313 - size_child));

						ImGui::BeginChild("Keybinds", ImVec2(339, 298), true);
						{
							static int k, m = 1;
							ImGui::Keybind("Aimbot Keybind", &k, &m);
						}
						ImGui::EndChild();

						break;

					case 1:
					{
						ImGui::SetCursorPos(ImVec2(193, 80 - size_child));

						ImGui::BeginChild("##玩家设置", ImVec2(696, 530), false);
						{
							{
								ImGui::SetCursorPos(ImVec2(0, 0 - size_child));

								ImGui::BeginChild("玩家选项", ImVec2(339, 253), true);
								{
									view::self();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(352, 0 - size_child)); //x 352 y 265 模块二大小与相对应的坐标

								ImGui::BeginChild("武器选项", ImVec2(339, 253), true);
								{
									view::weapons();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(0, 0 + (265 * 1) - size_child));

								ImGui::BeginChild("手机功能", ImVec2(339, 253), true);
								{
									view::mobile();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(352, 0 + (265 * 1) - size_child));

								ImGui::BeginChild("传送分类", ImVec2(339, 253), true);
								{
									view::teleport();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(0, 0 + (265 * 2) - size_child));

								ImGui::BeginChild("自定义传送", ImVec2(339, 253), true);
								{
									view::custom_teleport();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(352, 0 + (265 * 2) - size_child));

								ImGui::BeginChild("服装编辑器", ImVec2(339, 253), true);
								{
									view::outfit_slots();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(0, 0 + (265 * 3) - size_child));

								ImGui::BeginChild("装备编辑器", ImVec2(339, 253), true);
								{
									view::outfit_editor();
								}
								ImGui::EndChild();

								ImGui::SetCursorPos(ImVec2(352, 0 + (265 * 3) - size_child));

								ImGui::BeginChild("动作分类", ImVec2(339, 253), true);
								{
									view::animations();
								}
								ImGui::EndChild();
							}
						}
						ImGui::EndChild();
					}
					break;
					case 8:
						ImGui::SetCursorPos(ImVec2(193, 80 - size_child));
						ImGui::BeginChild("Configuration", ImVec2(339, 253), true);
						{
							ImGui::OptButton("A");
							help_marker("A");
							ImGui::OptButton("B");
							help_marker("B");
							ImGui::OptButton("C");
							help_marker("C");
							ImGui::OptButton("D");
							help_marker("D");
							ImGui::OptButton("E");
							help_marker("E");
							ImGui::OptButton("F");
							help_marker("F");
							ImGui::OptButton("G");
							help_marker("G");
							ImGui::OptButton("H");
							help_marker("H");
							ImGui::OptButton("I");
							help_marker("I");
							ImGui::OptButton("J");
							help_marker("J");
							ImGui::OptButton("K");
							help_marker("K");
							ImGui::OptButton("L");
							help_marker("L");
							ImGui::OptButton("M");
							help_marker("M");
							ImGui::OptButton("N");
							help_marker("N");
							ImGui::OptButton("O");
							help_marker("O");
							ImGui::OptButton("P");
							help_marker("P");
							ImGui::OptButton("Q");
							help_marker("Q");
							ImGui::OptButton("R");
							help_marker("R");
							ImGui::OptButton("S");
							help_marker("S");
							ImGui::OptButton("T");
							help_marker("T");
							ImGui::OptButton("U");
							help_marker("U");
							ImGui::OptButton("V");
							help_marker("V");
							ImGui::OptButton("W");
							help_marker("W");
							ImGui::OptButton("X");
							help_marker("X");
							ImGui::OptButton("Y");
							help_marker("Y");
							ImGui::OptButton("Z");
							help_marker("Z");
							ImGui::OptButton("a");
							help_marker("a");
							ImGui::OptButton("b");
							help_marker("b");
							ImGui::OptButton("c");
							help_marker("c");
						}
						ImGui::EndChild();
						break;
					}
				}
				ImGui::End();
			}
		}
	}
}