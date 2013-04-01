#include "stdafx.h"

#include "lua_context.h"
#include "iluacontext.h"

#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <boost/bind.hpp>

#include "context.inl"

namespace lul {

	class SomeLuaContext : public lul::iui::ILuaContext {

		struct Context {
			int increment;
			int upper_limit;
			int lower_limit;
			int state;
		};

		Context context;

	public:
		SomeLuaContext() {
			context.increment=1;
			context.upper_limit=4;
			context.lower_limit=0;
			context.state=0;
		}

	public:
		virtual void Register(lua_State* L) {
			using namespace luabind;
			open(L);
			module(L)
				[
					class_<Context>("Context")
					.def(constructor<>())
					.def_readwrite("increment",&Context::increment)
					.def_readwrite("upper_limit",&Context::upper_limit)
					.def_readwrite("lower_limit",&Context::lower_limit)
					.def_readwrite("state",&Context::state)
				];
			luabind::globals(L)["context"]=&context;

			std::string compiled=generated::Context();
			luaL_dostring(L,compiled.c_str());
		}

	private:

		Context& getContext() {
			return context;
		}
	};

	WALLAROO_REGISTER( SomeLuaContext );

	void CreateLuaContext(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "SomeLuaContext");
	}
}