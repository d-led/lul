#pragma once
#include <string>

namespace wallaroo {
	class Catalog;
};

namespace lul {
	void CreateTestLogic(std::string const& name,wallaroo::Catalog& catalog);
}