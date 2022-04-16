#pragma once
#include "SKSE/Trampoline.h"


class Hook_MeleeHit
{
public:
	static void install() {
		auto& trampoline = SKSE::GetTrampoline();
#if ANNIVERSARY_EDITION
		REL::Relocation<uintptr_t> hook{ REL::ID(38627) }; //64E760
		_ProcessHit = trampoline.write_call<5>(hook.address() + 0x4a8, processHit);
#else
		REL::Relocation<uintptr_t> hook{ REL::ID(37673) }; //628c20
		_ProcessHit = trampoline.write_call<5>(hook.address() + 0x3C0, processHit);
#endif
		INFO("Melee Hit hook installed.");
	}
private:
    static void processHit(RE::Actor* victim, RE::HitData& hitData);
    static inline REL::Relocation<decltype(processHit)> _ProcessHit;

};

class Hook_MainUpdate
{
public:
	static void install() {
		auto& trampoline = SKSE::GetTrampoline();
#if ANNIVERSARY_EDITION
		REL::Relocation<uintptr_t> hook{ REL::ID(36544) };  // 5D29F0, main loop
		_Update = trampoline.write_call<5>(hook.address() + 0x160, Update);
#else
		REL::Relocation<uintptr_t> hook{ REL::ID(35551) };  // 5AF3D0, main loop
		_Update = trampoline.write_call<5>(hook.address() + 0x11F, Update);
#endif
		INFO("Main Update hook installed.");
	}

private:
	static void Update(RE::Main* a_this, float a2);
	static inline REL::Relocation<decltype(Update)> _Update;

};

class Hook_PlayerUpdate
{
public:
	static void install() {
#if ANNIVERSARY_EDITION

		REL::Relocation<std::uintptr_t> PlayerCharacterVtbl{RE::VTABLE_PlayerCharacter[0]};
#else
		REL::Relocation<std::uintptr_t> PlayerCharacterVtbl{ RE::Offset::PlayerCharacter::Vtbl };
#endif
		
		_Update = PlayerCharacterVtbl.write_vfunc(0xAD, Update);
		INFO("Player update hook installed");
	}
private:
	static void Update(RE::PlayerCharacter* a_this, float a_delta);
	static inline REL::Relocation<decltype(Update)> _Update;
};

class Hooks {
public:
	static void install() {
		SKSE::AllocTrampoline(1 << 4);
		Hook_MeleeHit::install();
		//Hook_MainUpdate::install();
		Hook_PlayerUpdate::install();
	}
};

