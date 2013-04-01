print([===[initialized LuaLogicScript]===])

function Increment()
	if context.state < context.upper_limit then
		context.state=context.state+context.increment;
		Updated('counter',tostring(context.state))
	else
		Alert([[Upper limit of ]]..context.upper_limit..[[ reached]])
	end
end

function Decrement()
	if context.state > context.lower_limit then
		context.state = context.state-context.increment;
		Updated('counter',tostring(context.state))
	else
		Alert([[Lower limit of ]]..context.lower_limit..[[ reached]])
	end
end

function ProcessEvent(name)
	if name=='Decrement' then
		Decrement()
	elseif name=='Increment' then
		Increment()
	else
		UnknownEvent()
	end
end
