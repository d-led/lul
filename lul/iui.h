#pragma once

#include <memory>
#include <string>

#include "wallaroo/registered.h"

namespace lul {

	namespace iui {

		struct ILogic : public wallaroo::Device {
			virtual void Configure()=0;
			virtual void ProcessEvent(std::string const& name)=0;
			virtual ~ILogic(){}
		};

		struct IView : public wallaroo::Device {
			virtual void ReceiveEvent(std::string const& name)=0;
			virtual void ShowValue(std::string const& name,std::string const& value)=0;
			virtual void Alert(std::string const& message)=0;
			virtual ~IView(){}
		};
	}

}