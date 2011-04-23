//-----------------------------------------------------------------------------
//��װ��¼
//
//ע��Ŀǰ��loader.hpp�ķ�װ�����ڿ��Ƶ�����dbg.hpp����Ҫ,�����漰����Ϣ��Hook
//    ����ϢHook��ж�أ����ж���Ϣ�Ļص�����
//    
//    û�з�װ�ɹ���ע�͵�����
//
//-----------------------------------------------------------------------------


//******************************************************************************
//�� loader.hpp ͷ�ļ����з�װ  write by dreamzgj 
//******************************************************************************
using namespace System;

namespace IDACSharp
{
#ifndef __LOADER_H__
#define __LOADER_H__

	public enum class Enum_Hook_Type_T
	{
		HT_IDP,         // Hook to the processor module.
		// The callback will receive all idp_notify events.
		// See file idp.hpp for the list of events.
		HT_UI,          // Hook to the user interface.
		// The callback will receive all ui_notification_t events.
		// See file kernwin.hpp for the list of events.
		HT_DBG,         // Hook to the debugger.
		// The callback will receive all dbg_notification_t events.
		// See file dbg.hpp for the list of events.
		HT_IDB,         // Hook to the database events.
		// These events are separated from the HT_IDP group
		// to speed up things (there are too many plugins and
		// modules hooking to the HT_IDP). Some essential events
		// are still generated in th HT_IDP group:
		// make_code, make_data, undefine, rename, add_func, del_func.
		// This list is not exhaustive.
		// A common trait of all events in this group: the kernel
		// does not expect any reaction to the event and does not
		// check the return code. For event names, see the idp_event_t
		// in idp.hpp
		HT_DEV,         // Internal debugger events.
		// Not stable and undocumented for the moment
		HT_LAST
	};

	public ref class Ida_Loader
	{
	public:
		//public delegate bool Hook_Cb_T(Object^ User_Data,int Notification_Code, ...array<Object^>^ Args);
		//
		//static bool Hook_To_Notification_Point(Enum_Hook_Type_T Hook_Type,Hook_Cb_T Cb,Object^ User_Data)
		//{
		//	
		//}

		//static int UnHook_From_Notification_Point(Enum_Hook_Type_T Hook_Type,Hook_Cb_T Cb,Object^ User_Data)
		//{
		//	
		//}

		//static int Invoke_CallBacks(Enum_Hook_Type_T Hook_Type,int Notification_Code,...array<Object^>^ Args)
		//{
		//	
		//}
	};
	

#endif
}