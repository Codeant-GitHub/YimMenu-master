

/**
 * @file exception_handler.cpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "common.hpp"
#include "exception_handler.hpp"

#include "stack_trace.hpp"

namespace big
{
	inline auto hash_stack_trace(std::vector<uint64_t> stack_trace)
	{
		auto data        = reinterpret_cast<const char*>(stack_trace.data());
		std::size_t size = stack_trace.size() * sizeof(uint64_t);

		return std::hash<std::string_view>()({data, size});
	}

	exception_handler::exception_handler()
	{
		m_old_error_mode    = SetErrorMode(0);
		m_exception_handler = SetUnhandledExceptionFilter(&vectored_exception_handler);
	}

	exception_handler::~exception_handler()
	{
		SetErrorMode(m_old_error_mode);
		SetUnhandledExceptionFilter(reinterpret_cast<decltype(&vectored_exception_handler)>(m_exception_handler));
	}

	inline static stack_trace trace;
	LONG vectored_exception_handler(EXCEPTION_POINTERS* exception_info)
	{
		const auto exception_code = exception_info->ExceptionRecord->ExceptionCode;
		if (exception_code == EXCEPTION_BREAKPOINT || exception_code == DBG_PRINTEXCEPTION_C || exception_code == DBG_PRINTEXCEPTION_WIDE_C)
			return EXCEPTION_CONTINUE_SEARCH;

		static std::set<std::size_t> logged_exceptions;

		trace.new_stack_trace(exception_info);
		const auto trace_hash = hash_stack_trace(trace.frame_pointers());
		if (const auto it = logged_exceptions.find(trace_hash); it == logged_exceptions.end())
		{
			//LOG(FATAL) << trace;
			Logger::FlushQueue();

			logged_exceptions.insert(trace_hash);
		}

		//ZyanU64 opcode_address = exception_info->ContextRecord->Rip;
		//ZydisDisassembledInstruction instruction;
		//ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LONG_64, opcode_address, reinterpret_cast<void*>(opcode_address), 32, &instruction);

		//exception_info->ContextRecord->Rip += instruction.info.length;

		return EXCEPTION_CONTINUE_EXECUTION;
	}
}