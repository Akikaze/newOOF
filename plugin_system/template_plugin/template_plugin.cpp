#include "template_plugin.hpp"

extern "C"
Interface *
load
()
{
	return new template_plugin ;
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
