#pragma once
#include <string>

namespace wallaroo {
	class Catalog;
};

namespace lul {
	void CreateLuaLogic(std::string const& name,wallaroo::Catalog& catalog);
}