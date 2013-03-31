#include "stdafx.h"

#include "lua_logic.h"

#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

#include <lua.hpp>

#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <boost/bind.hpp>

int f(int x, int y)
{
    return x + y;
}

namespace lul {
	class LuaCounterLogic : public lul::iui::ILogic {
	lua_State *L;
	wallaroo::Plug<lul::iui::IView> view;
	public:
		LuaCounterLogic():
			view( "view", RegistrationToken() ),
			L(lua_open())
		{
			using namespace luabind;
			module(L) [
				def("UnknownEvent", tag_function<void(std::string)>(boost::bind(&LuaCounterLogic::UnknownEvent,this,_1)))
			];

			std::cout<<"Created LuaCounterLogic"<<std::endl;
		}

		virtual ~LuaCounterLogic() {
			lua_close(L);
			L=0;
		}

	public:
		virtual void ProcessEvent(std::string const& name) {
			std::cout<<"LuaCounterLogic received event: "<<name<<std::endl;
		}

	//private:
		void UnknownEvent(std::string name) {
			std::cout<<"Unknown event: "<<name<<std::endl;
		}
	};

	WALLAROO_REGISTER( LuaCounterLogic );

	void CreateLuaLogic(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "LuaCounterLogic");
	}
}