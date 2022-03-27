#pragma once
class offsets
{
public:
	static inline float* g_deltaTime = (float*)REL::ID(523660).address();                            // 2F6B948
	static inline float* g_deltaTimeRealTime = (float*)REL::ID(523661).address();                  // 2F6B94C


	typedef void(_fastcall* _setIsGhost)(RE::Actor* actor, bool isGhost);
	static inline REL::Relocation<_setIsGhost> setIsGhost{ REL::ID(36287) };
};