#pragma once

#include <string>

namespace wallaroo {
	class Catalog;
};

namespace lul {
	void CreateLuaContext(std::string const& name,wallaroo::Catalog& catalog);
}
