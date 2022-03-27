#include "include/guardCounter.h"
#include "include/offsets.h"
#include "include/simpleIni.h"
void guardCounter::update() {
	if (gc_Timer > 0) {
		gc_Timer -= *offsets::g_deltaTimeRealTime;
		if (gc_Timer <= 0) {
			auto pc = RE::PlayerCharacter::GetSingleton();
			if (pc) {
				pc->RemoveSpell(gc_triggerSpell);
				pc->SetGraphVariableBool("Val_GuardCounter", false);
			}
			//RE::DebugNotification("guard counter stop");
		}
	}
}

void guardCounter::registerBlock() {
	//DEBUG("registering block");
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (pc) {
		pc->AddSpell(gc_triggerSpell);
		pc->SetGraphVariableBool("Val_GuardCounter", true);
		gc_Timer = gc_Time;
		//DEBUG(gc_Timer);
	}
	//RE::DebugNotification("guard counter start!");
}

void guardCounter::readSettings() {
	INFO("Loading settings...");
	CSimpleIniA ini;
#define SETTINGFILE_PATH "Data\\SKSE\\Plugins\\EldenCounter.ini"
	ini.LoadFile(SETTINGFILE_PATH);
	gc_Time = ini.GetLongValue("General", "Time");
	INFO("Settings loaded.");
}

void guardCounter::loadData() {
	INFO("Loading data...");
	gc_triggerSpell = RE::TESDataHandler::GetSingleton()->LookupForm<RE::SpellItem>(0x12CE, "EldenCounter.esp");
	if (!gc_triggerSpell) {
		ERROR("Error: spell not found! Enable EldenCounter.esp");
	}
}