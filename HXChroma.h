#pragma once

#include <Windows.h>

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <hidusage.h>
#include <thread>
#include <chrono>

#include <hidapi.h>
#include <hidapi_winapi.h>

#pragma comment(lib, "hidapi.lib")