
#pragma once
#include "common.hpp"
#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "gta/joaat.hpp"
#include "gta/net_array.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"

// Credits: QuickNET
namespace big
{
	static float old_percent = NAN;

	eTransitionState last_state = eTransitionState::TRANSITION_STATE_EMPTY;
	void looped::hud_transition_state()
	{
		const auto state = *scr_globals::transition_state.as<eTransitionState*>();
		const std::vector<std::string_view> transition_states = {"TRANSITION_STATE_EMPTY"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_SINGLEPLAYER_SWOOP_UP"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_MULTIPLAYER_SWOOP_UP"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CREATOR_SWOOP_UP"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_PRE_HUD_CHECKS"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_HUD_EXIT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_FOR_SUMMON"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_SINGLEPLAYER_SWOOP_DOWN"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_MULTIPLAYER_SWOOP_DOWN"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CANCEL_JOINING"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETRY_LOADING"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETRY_LOADING_SLOT_1"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETRY_LOADING_SLOT_2"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETRY_LOADING_SLOT_3"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETRY_LOADING_SLOT_4"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_ON_INVITE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_PREJOINING_FREEMODE_SESSION_CHECKS"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_FOR_FRESH_JOIN_FREEMODE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_FREEMODE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CONFIRM_FREEMODE_SESSION_JOINING"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_JOIN_FREEMODE_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CREATION_ENTER_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_PRE_FREEMODE_LAUNCH_SCRIPT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_FREEMODE_TEAMFULL_CHECK"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_START_FREEMODE_LAUNCH_SCRIPT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_FREEMODE_TRANSITION_CREATE_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_IS_FREEMODE_AND_TRANSITION_READY"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_FREEMODE_SWOOP_DOWN"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_POST_BINK_VIDEO_WARP"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_FREEMODE_FINAL_SETUP_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_MOVE_FREEMODE_TO_RUNNING_STATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_FREEMODE_HOW_TO_TERMINATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_START_CREATOR_PRE_LAUNCH_SCRIPT_CHECK"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_START_CREATOR_LAUNCH_SCRIPT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CREATOR_TRANSITION_CREATE_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_IS_CREATOR_AND_TRANSITION_READY"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CREATOR_SWOOP_DOWN"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CREATOR_FINAL_SETUP_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_MOVE_CREATOR_TO_RUNNING_STATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_PREJOINING_TESTBED_SESSION_CHECKS"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_FOR_FRESH_JOIN_TESTBED"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_FOR_FRESH_HOST_TESTBED"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_TESTBED"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_LOOK_TO_HOST_SESSION_TESTBED"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_CONFIRM_TESTBED_SESSION_JOINING"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_JOIN_TESTBED_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_START_TESTBED_LAUNCH_SCRIPT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TESTBED_TRANSITION_CREATE_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_IS_TESTBED_AND_TRANSITION_READY"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TESTBED_SWOOP_DOWN"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TESTBED_FINAL_SETUP_PLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_MOVE_TESTBED_TO_RUNNING_STATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TESTBED_HOW_TO_TERMINATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_QUIT_CURRENT_SESSION_PROMPT"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_FOR_TRANSITION_SESSION_TO_SETUP"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TERMINATE_SINGLEPLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_TERMINATE_SINGLEPLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_KICK_TERMINATE_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TERMINATE_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_TERMINATE_SESSION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TERMINATE_SESSION_AND_HOLD"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TERMINATE_SESSION_AND_MOVE_INTO_HOLDING_STATE"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TEAM_SWAPPING_CHECKS"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_RETURN_TO_SINGLEPLAYER"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_FOR_SINGLEPLAYER_TO_START"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAITING_FOR_EXTERNAL_TERMINATION_CALL"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_TERMINATE_MAINTRANSITION"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAIT_FOR_DIRTY_LOAD_CONFIRM"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_DLC_INTRO_BINK"_T, "BACKEND_LOOPED_HUD_TRANSITION_STATE_SPAWN_INTO_PERSONAL_VEHICLE"_T};

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0)
			return;

		// When freemode script loaded remove loading screen.
		if (state == eTransitionState::TRANSITION_STATE_WAIT_JOIN_FM_SESSION && DLC::GET_IS_LOADING_SCREEN_ACTIVE())
		{
			SCRIPT::SHUTDOWN_LOADING_SCREEN();
		}

		if ((last_state == state && state != eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER) || state == eTransitionState::TRANSITION_STATE_EMPTY || state > eTransitionState::TRANSITION_STATE_SPAWN_INTO_PERSONAL_VEHICLE)
		{
			return;
		}

		if (state != eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER && HUD::BUSYSPINNER_IS_ON())
		{
			HUD::BUSYSPINNER_OFF();
		}

		if ((int)state > 0 && (int)state < transition_states.size())
		{
			rage::scrThread* freemode{};
			if (state == eTransitionState::TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER
			    && (freemode = gta_util::find_script_thread("freemode"_J), freemode && freemode->m_net_component))
			{
				int num_array_handlers{};
				int received_array_handlers{};

				while (
				    auto handler = g_pointers->m_gta.m_get_host_array_handler_by_index((CGameScriptHandlerNetComponent*)freemode->m_net_component, num_array_handlers++))
					if (handler->m_flags & 1)
						received_array_handlers++;

				if (num_array_handlers == 0)
					num_array_handlers = 1;

				float percent = round((static_cast<float>(received_array_handlers) / num_array_handlers) * 100);

				if (percent != old_percent)
				{
					HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(std::format("{}: {}%", "BACKEND_LOOPED_HUD_TRANSITION_STATE_WAITING_FOR_HOST_BROADCAST_DATA"_T, percent).c_str());
					HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
				}

				old_percent = percent;
			}
			else
			{
				old_percent = NAN;
				HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(transition_states[(int)state].data());
				HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
			}
		}

		last_state = state;
	}
}