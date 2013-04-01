namespace generated {
 std::string Context() {
  return
"print([===[initialized LuaLogicScript]===])\n"
		"function Increment()\n"
		"	if context.state < context.upper_limit then\n"
		"		context.state=context.state+context.increment;\n"
		"		Updated('counter',tostring(context.state))\n"
		"	else\n"
		"		Alert([[Upper limit of ]]..context.upper_limit..[[ reached]])\n"
		"	end\n"
		"end\n"
		"function Decrement()\n"
		"	if context.state > context.lower_limit then\n"
		"		context.state = context.state-context.increment;\n"
		"		Updated('counter',tostring(context.state))\n"
		"	else\n"
		"		Alert([[Lower limit of ]]..context.lower_limit..[[ reached]])\n"
		"	end\n"
		"end\n"
		"function ProcessEvent(name)\n"
		"	if name=='Decrement' then\n"
		"		Decrement()\n"
		"	else if name=='Increment' then\n"
		"		Increment()\n"
		"	else\n"
		"		UnknownEvent()\n"
		"	end\n"
		"end\n"
		"end\n"
		  ;
 }
}
