#include <ida.hpp>
#include <idp.hpp>
#include <expr.hpp>
#include <bytes.hpp>
#include <loader.hpp>
#include <kernwin.hpp>

#include "IDACSharp.h"

using namespace IDACSharp;

int  idaapi init(void)  { 
	msg("---------------------------------------------------------------------------\n");
	msg("���ڳ�ʼ�� IDACSharp...\n");

	bool b = Loader::Init();
	msg("---------------------------------------------------------------------------\n");

	if (b)
		return PLUGIN_KEEP;
	else
		return PLUGIN_SKIP;
}

void idaapi term(void)  { 
	msg("���ڽ��� IDACSharp...\n");

	Loader::Term();
}

void idaapi run(int arg){ 
	msg("���� IDACSharp...\n");

	try{
		//warning("IDACSharp���������");
		Loader::Start();                                   
	}
	catch(...)
	{
		msg("����IDACSharp�쳣��");
		//Loader::Term();
		//Loader::Init();
	}
}

char comment[]		 = "IDACSharp���";
char help[]			 = "����һ��IDACSharp�����������C#�ṩIDA�����ӿڣ��Է���ʹ��C#����IDA���";
char wanted_name[]	 = "IDACSharp";
char wanted_hotkey[] = "Alt-8";

extern "C"
{
	plugin_t PLUGIN =	{
		IDP_INTERFACE_VERSION,
		0,                    // plugin flags
		init,                 // initialize
		term,                 // terminate. this pointer may be NULL.
		run,                  // invoke plugin
		comment,              // long comment about the plugin (status line or hint)
		help,                 // multiline help about the plugin
		wanted_name,          // the preferred short name of the plugin
		wanted_hotkey         // the preferred hotkey to run the plugin
	};
}