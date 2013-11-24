#include "stdafx.h"

#include "lua_logic.h"

#include "../lul/iui.h"
#include "iluacontext.h"

#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <boost/bind.hpp>

namespace lul {
	class LuaLogic : public lul::iui::ILogic {
		lua_State *L;
		wallaroo::Plug<lul::iui::IView> view;
		wallaroo::Plug<lul::iui::ILuaContext> context;
	public:
		LuaLogic():
			view("view",RegistrationToken()),
			context("context",RegistrationToken()),
			L(lua_open())
		{
			std::cout<<"Created LuaLogic"<<std::endl;
		}

		virtual ~LuaLogic() {
			lua_close(L);
			L=0;
		}

	public:

		virtual void Configure() {
			using namespace luabind;
			//can be reduced to minimum
			luaL_openlibs(L);
			module(L) [
				def("UnknownEvent", tag_function<void(std::string)>(boost::bind(&LuaLogic::UnknownEvent,this,_1))),
				def("Alert", tag_function<void(std::string)>(boost::bind(&LuaLogic::Alert,this,_1))),
				def("Updated", tag_function<void(std::string,std::string)>(boost::bind(&LuaLogic::Updated,this,_1,_2)))
			];
			if (context)
				context->Register(L);
		}

		virtual void ProcessEvent(std::string const& name) {
			// quite unsafe
			std::string call=std::string("ProcessEvent[====[")+name+("]====];");
			luaL_dostring(L,call.c_str());
		}

	private:
		void UnknownEvent(std::string const& name) const {
			Alert(std::string("Unknown event: ")+name);
		}

		void Alert(std::string const& message) const {
			if (view)
				view->Alert(message);
		}

		void Updated(std::string key,std::string value) const {
			if (view)
				view->ShowValue(key,value);
		}
	};

	WALLAROO_REGISTER( LuaLogic );

	void CreateLuaLogic(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "LuaLogic");
	}
}