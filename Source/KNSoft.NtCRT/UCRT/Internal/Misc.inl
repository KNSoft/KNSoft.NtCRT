#pragma once

#include "../../NtCRT.inl"

#include <internal/locks.cpp>
#include <internal/GetModuleFileNameA.cpp>
#include <internal/SetEnvironmentVariableA.cpp>

#define reentrancy_sentinel ucrt_reentrancy_sentinel
#include <internal/per_thread_data.cpp>
#undef reentrancy_sentinel
