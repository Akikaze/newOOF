#include "template_plugin.hpp"

extern "C"
Interface *
create
()
{
	return new template_plugin ;
}

extern "C"
void
destroy
(
	Interface * object
)
{
	delete object ;
}

template_plugin::template_plugin
()
: Interface()
{
	name_ = "template_plugin" ;
	description_ = "Template of a plugin for the plugin system of OOF" ;
}

template_plugin::~template_plugin
()
{
	
}
