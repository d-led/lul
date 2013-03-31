#include "stdafx.h"

#include "lua_logic.h"

#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

#include <lua.hpp>

#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <boost/bind.hpp>

namespace {
	const char* LuaLogicScript =
		"print([[initialized LuaLogicScript]]);"
		"lower_limit=0;"
		"upper_limit=4;"
		"counter=lower_limit;"
		"function Increment() if counter<upper_limit then counter=counter+1; Updated() else Alert([[Upper limit of ]]..upper_limit..[[ reached]]) end end;"
		"function Decrement() if counter>lower_limit then counter=counter-1; Updated() else Alert([[Lower limit of ]]..lower_limit..[[ reached]]) end end;"
		;
}

namespace lul {
	class LuaCounterLogic : public lul::iui::ILogic {
		lua_State *L;
		wallaroo::Plug<lul::iui::IView> view;
	public:
		LuaCounterLogic():
			view("view",RegistrationToken()),
			L(lua_open())
		{
			using namespace luabind;
			luaL_openlibs(L);
			module(L) [
				def("UnknownEvent", tag_function<void(std::string)>(boost::bind(&LuaCounterLogic::UnknownEvent,this,_1))),
				def("Alert", tag_function<void(std::string)>(boost::bind(&LuaCounterLogic::Alert,this,_1))),
				def("Updated", tag_function<void()>(boost::bind(&LuaCounterLogic::Updated,this)))
			];
			luaL_dostring(L,LuaLogicScript);
			std::cout<<"Created LuaCounterLogic"<<std::endl;
		}

		virtual ~LuaCounterLogic() {
			lua_close(L);
			L=0;
		}

	public:
		virtual void ProcessEvent(std::string const& name) {
			if (name=="Increment")
				luabind::call_function<void>(L, "Increment", name);
			else if (name=="Decrement")
				luabind::call_function<void>(L, "Decrement", name);
			else
				luabind::call_function<void>(L, "UnknownEvent", name);
		}

	private:
		void UnknownEvent(std::string const& name) const {
			Alert(std::string("Unknown event: ")+name);
		}

		void Alert(std::string const& message) const {
			if (view)
				view->Alert(message);
		}

		void Updated() const {
			if (view)
				view->ShowValue("counter",CounterValue());
		}

		std::string CounterValue() const {
			std::stringstream s;
			int count=luabind::object_cast<int>(luabind::globals(L)["counter"]);
			s<<count;
			return s.str();
		}
	};

	WALLAROO_REGISTER( LuaCounterLogic );

	void CreateLuaLogic(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "LuaCounterLogic");
	}
}