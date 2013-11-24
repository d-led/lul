_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'lul'

includedirs { 
	'./lul',
	'./luabind',
	'./wallaroo'
}

local OS = os.get()
local settings = {
	links = {
		linux = { 'lua' },
		windows = { 'lua5.1' },
		macosx = { 'lua' }
	}
}

defines { 'BOOST_NO_VARIADIC_TEMPLATES' }

-- make_console_app('my_project', { 'my_project.cpp' } )

make_static_lib('luabind',{'./luabind/src/*.cpp'})

make_console_app('lul_example',{'./example/*.h','./example/*.cpp'})

links { 'luabind' , settings.links[OS] }

make_cpp11()
