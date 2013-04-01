#pragma once

#include <lua.hpp>

#include "wallaroo/registered.h"

namespace lul {

	namespace iui {
		struct ILuaContext : public wallaroo::Device {
			virtual void Register(lua_State*)=0;
			virtual ~ILuaContext() {}
		};
	}

}