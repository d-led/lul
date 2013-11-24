// lul_example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../lul/iui.h"
#include "wallaroo/catalog.h"
#include "some_logic.h"
#include "some_ui.h"
#include "lua_logic.h"
#include "lua_context.h"

int main(int argc, char* argv[])
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
	lul::CreateLuaContext("LuaCounterContext",catalog);
	// change the logic plug
	wallaroo_within(catalog)
	{
		use("LuaCounterLogic").as("logic").of("MainUI");
		use("MainUI").as("view").of("LuaCounterLogic");
		use("LuaCounterContext").as("context").of("LuaCounterLogic");
	}
	
	//configure
	std::shared_ptr<lul::iui::ILogic> LuaCounterLogic = catalog["LuaCounterLogic"];
	LuaCounterLogic->Configure();

	//send some events
	MainUI->ReceiveEvent("test");
	
	MainUI->ReceiveEvent("Increment");
	MainUI->ReceiveEvent("Increment");
	MainUI->ReceiveEvent("Increment");
	MainUI->ReceiveEvent("Increment");
	
	MainUI->ReceiveEvent("Increment");
	MainUI->ReceiveEvent("Increment");
	
	MainUI->ReceiveEvent("Decrement");
	MainUI->ReceiveEvent("Decrement");
	MainUI->ReceiveEvent("Decrement");
	MainUI->ReceiveEvent("Decrement");
	
	MainUI->ReceiveEvent("Decrement");
	MainUI->ReceiveEvent("Decrement");
	
	return 0;
}

