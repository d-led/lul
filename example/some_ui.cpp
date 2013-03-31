#include "stdafx.h"

#include "some_ui.h"

#include "..\lul\iui.h"
#include "wallaroo/catalog.h"
#include "wallaroo/registered.h"

namespace lul {

	class SomeUI : public lul::iui::IView
	{
	public:
		SomeUI():
			logic( "logic", RegistrationToken() )
		{
			std::cout<<"Created SomeUI"<<std::endl;
		}

	public:
		virtual void ReceiveEvent(std::string const& name) {
			if (logic) {
				logic->ProcessEvent(name);
			}
		}

		virtual void ShowValue(std::string const& name,std::string const& value) {
			std::cout<<"Showing: "<<name<<"="<<value<<std::endl;
		}

		virtual void Alert(std::string const& message) {
			std::cout<<"Alert: "<<message<<"!"<<std::endl;
		}

	private:
		wallaroo::Plug<lul::iui::ILogic> logic;
	};

	WALLAROO_REGISTER( SomeUI );

	void CreateSomeUI(std::string const& name,wallaroo::Catalog& catalog)
	{
		catalog.Create(name, "SomeUI");
	}
}