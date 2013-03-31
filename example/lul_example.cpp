// lul_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "some_logic.h"
#include "some_ui.h"
#include "lua_logic.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace wallaroo;

	// instantiate objects in a catalog
	Catalog catalog;
	lul::CreateSomeUI("MainUI",catalog);
	lul::CreateTestLogic("TestLogic",catalog);

	// resolve dependencies using object names
	wallaroo_within(catalog)
	{
		use("TestLogic").as("logic").of("MainUI");
	}

	// get an instance of the ui
	std::shared_ptr<lul::iui::IView> MainUI = catalog["MainUI"];
	MainUI->ReceiveEvent("test");

	lul::CreateLuaLogic("LuaCounterLogic",catalog);
	// change the logic plug
	wallaroo_within(catalog)
	{
		use("LuaCounterLogic").as("logic").of("MainUI");
	}
	MainUI->ReceiveEvent("test");

	
	return 0;
}

