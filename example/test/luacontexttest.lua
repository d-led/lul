dofile[[../context.lua]]

--mocks---------------------------

context= {
	state=0,
	increment=1,
	lower_limit=0,
	upper_limit=2
}

function UnknownEvent()
end

local alerted=false
function Alert(msg)
	alerted=true
end

function Updated(key,value)
end

--test-----------------------------

assert(context.state==0)
Decrement()
assert(alerted)
assert(context.state==0)

Increment()
assert(context.state==1)

Increment()
assert(context.state==2)

alerted=false
Increment()
assert(alerted)
assert(context.state==2)
