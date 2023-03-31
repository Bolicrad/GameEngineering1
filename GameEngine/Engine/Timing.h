#pragma once
#include <Windows.h>
#include <assert.h>
#include <limits.h>
#define DESIRED_FPS 60.0f
#define DESIRED_FRAMETIME_MS (1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS (2 * DESIRED_FRAMETIME_MS)



namespace Engine{
	namespace Timing {
		LARGE_INTEGER PerformanceFrequency = { 0 };

		bool Initialize() {
			if (!QueryPerformanceFrequency(&PerformanceFrequency))
				return false;
			return true;
		}

		LONGLONG GetCurrentTickCounter() {
			LARGE_INTEGER CurrentFrameCounter;

			BOOL success = QueryPerformanceCounter(&CurrentFrameCounter);
			assert(success == TRUE);

			return CurrentFrameCounter.QuadPart;
		}

		float GetTimeDiff_ms(LONGLONG i_StartTime, LONGLONG i_EndTime) {
			if (PerformanceFrequency.QuadPart == 0) {
				bool success = Initialize();
				assert(success);
			}

			return (1000.0f * static_cast<float>(i_EndTime - i_StartTime) / PerformanceFrequency.QuadPart);
		}

		float GetLastFrameTime_ms() {
			static LONGLONG lastFrameStartTick = 0;
			float result;
			LONGLONG currentTick = GetCurrentTickCounter();
			if (lastFrameStartTick) {
				result = GetTimeDiff_ms(lastFrameStartTick, currentTick);
				if (result > 2 * MAX_FRAMETIME_MS)result = MAX_FRAMETIME_MS;
			}
			else {
				result = 13.3f;
			}
			lastFrameStartTick = currentTick;

			return result;
		}
	}
}