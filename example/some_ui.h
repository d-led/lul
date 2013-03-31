#pragma once
#include <string>

namespace wallaroo {
	class Catalog;
};

namespace lul {
	void CreateSomeUI(std::string const& name,wallaroo::Catalog& catalog);
}