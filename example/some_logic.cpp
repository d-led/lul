#include "stdafx.h"

#include "some_logic.h"

#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

namespace lul {

	class SomeUILogic : public lul::iui::ILogic {
	public:
		SomeUILogic() {
			std::cout<<"Created SomeUILogic"<<std::endl;
		}

	public:
		virtual void ProcessEvent(std::string const& name) {
			std::cout<<"SomeUILogic received event: "<<name<<std::endl;
		}
	};

	WALLAROO_REGISTER( SomeUILogic );

	void CreateTestLogic(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "SomeUILogic");
	}
}