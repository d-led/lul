- [lul](#lul)
- [walkthrough](#walkthrough)
	- [Dependency inversion](#dependency-inversion)
	- [reconfiguring the instances](#reconfiguring-the-instances)
	- [LuaCounterLogic](#luacounterlogic)
- [license](#license)

lul
===

This project shows an example of using lua as a scriptable ui logic component.

The binding is done via [luabind](http://www.rasterbar.com/products/luabind/docs.html)
and the dependency injection using [wallaroo](https://code.google.com/p/wallaroo/).

walkthrough
===========

Dependency inversion
--------------------

Starting from [lul_example.cpp](example/lul_example.cpp):

```cpp
Catalog catalog;
lul::CreateSomeUI("MainUI",catalog);
lul::CreateTestLogic("TestLogic",catalog);
```

`catalog` is here the named object pool that can contain instances of the interfaces defined in [lul/iui.h](lul/iui.h). There you will find an `IView` and an `ILogic` simple interfaces. The two `lul::Create*` calls instantiate and register the named objects that implement the interfaces. As you can see, the knowledge of the concrete types is not required here.

The implementation of the UI contains a placeholder for the logic component as a Wallaroo 'plug':

```cpp
class SomeUI : public lul::iui::IView
{
public:
	SomeUI(): logic( "logic", RegistrationToken() ) {}

	// ...

private:
	wallaroo::Plug<lul::iui::ILogic> logic;
};
```

Now, the components are linked together using the special Wallaroo syntax that is quite natural language - readable:

```cpp
wallaroo_within(catalog)
{
	use("TestLogic").as("logic").of("MainUI");
}
```

All objects are specified by their name, so you need discipline, error handling or a fool-proof configuration to resolve all the necessary dependencies. The 'TestLogic' logic implementation does nothing apart from echoing events to the console. Hence, when you call the following,

Using the interface instances

```cpp
auto MainUI = catalog["MainUI"];
MainUI->ReceiveEvent("test");
```

the UI forwards the call to it's logic meber that echoes `SomeUILogic received event: test`.

reconfiguring the instances
---------------------------

The main strength of Wallaroo is perhaps the ability to reconfigure the dependency resolutions at runtime. Thus, calling

```cpp
wallaroo_within(catalog)
{
	use("LuaCounterLogic").as("logic").of("MainUI");
	use("MainUI").as("view").of("LuaCounterLogic");
	use("LuaCounterContext").as("context").of("LuaCounterLogic");
}
```

updates the dependency of 'MainUI', and adds a new dependency of the dependency - the `LuaCounterContext`. What exactly is runtime-linked to what can be read in plain English from the code itself.

Now, the behavior of the UI is totally changed, and it uses two more components.

LuaCounterLogic
---------------

The logic component implemented in Lua just as an example. The Lua script _text_ is embedded into the c++ executable for demo purposes. Any other kind of script deployment can replace this one. The logic component knows of the UI interface and of the state interface, which is provided in [example/iluacontext.h](example/iluacontext.h). The interface is extermely simple - it can only accept a Lua state, into which it binds a C++ context class, which will be instantiated from Lua. The state is a simple counter with an upper and a lower limit.

The logic component exposes only three functions to the Lua state: `UnknownEvent`, `Alert` and `Updated` that are conveniently bound to the logic instance using LuaBind:

```cpp
luaL_openlibs(L);
module(L) [
	def("UnknownEvent",
		tag_function<void(std::string)>(
			boost::bind(&LuaLogic::UnknownEvent,this,_1)
		)),
	//...
];
```



license
=======

No specific license is attached. Use at your own risk.
