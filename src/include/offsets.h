#pragma once
class offsets
{
public:
#if ANNIVERSARY_EDITION
	static inline float* g_deltaTime = (float*)REL::ID(410199).address();                         // 30064C8
	static inline float* g_deltaTimeRealTime = (float*)REL::ID(410200).address();                 // 30064CC
#else 
	static inline float* g_deltaTime = (float*)REL::ID(523660).address();                            // 2F6B948
	static inline float* g_deltaTimeRealTime = (float*)REL::ID(523661).address();                  // 2F6B94C
#endif
};