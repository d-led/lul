#include "stdafx.h"

#include "lua_logic.h"

#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

namespace lul {

	class LuaCounterLogic : public lul::iui::ILogic {
	public:
		LuaCounterLogic() {
			std::cout<<"Created LuaCounterLogic"<<std::endl;
		}

	public:
		virtual void ProcessEvent(std::string const& name) {
			std::cout<<"LuaCounterLogic received event: "<<name<<std::endl;
		}
	};

	WALLAROO_REGISTER( LuaCounterLogic );

	void CreateLuaLogic(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "LuaCounterLogic");
	}
}