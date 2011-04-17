// IDACSharp.h

#include <kernwin.hpp>

#include "KernelWin.h"

#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

namespace IDACSharp {

	// ������
	public ref class Loader
	{
	private:
		// ����������
		static Type^ loaderType = nullptr;

		// ˽�й��캯�������ڼ���CSharp������
		static Loader(){
			msg("����CSharp������...\n");

			String^ path = Path::Combine(AppDomain::CurrentDomain->BaseDirectory, "CSharp");
			msg("CSharpĿ¼��%s\n", path);

			if(!Directory::Exists(path)){
				msg("Ŀ¼%s�����ڣ�\n", path);
				return;
			}

			String^ file = Path::Combine(path, "CSharpLoader.dll");
			if(!File::Exists(file)){
				msg("δ�ҵ�CSharp������%s�����CShapLoader.dll�ļ���������λ�ã�\n", file);
				return;
			}

			msg("׼�������ļ�%s\n", file);

			try{
				Assembly^ a = Assembly::LoadFile(file);
				if(a == nullptr) {
					msg("���س���ʧ�ܣ�\n");
					return;
				}

				array<Type^>^ types = a->GetTypes();

				loaderType = a->GetType("CSharpLoader.Loader");
				if(loaderType == nullptr) {
					msg("��������ʧ�ܣ�\n");
					return;
				}
			}
			catch(ReflectionTypeLoadException^ e){
				msg("�����쳣��\n");

				WriteLine(e->ToString());
				WriteLine(e->LoaderExceptions[0]->ToString());
			}
			catch(Exception^ e){
				msg("�����쳣��\n");

				WriteLine(e->ToString());
			}

			msg("������ɣ�\n");
		}

		static MethodInfo^ FindMethod(String^ name){
			if(loaderType == nullptr){
				msg("δ�������ͣ�\n");
				return nullptr;
			}

			return loaderType->GetMethod(name);
		}

	public:
		// ��ʼ��
		static bool Init(){
			MethodInfo^ method = FindMethod("Init");
			if(loaderType == nullptr){
				msg("δ�ҵ�����%s����ȷ���Ѱ�IDACSharp.dll�ŵ�IDA��Ŀ¼�£�\n", "Init");
				return false;
			}

			return (bool)method->Invoke(nullptr, nullptr);
		}

		// ����
		static void Start(){
			MethodInfo^ method = FindMethod("Start");
			if(loaderType == nullptr){
				msg("δ�ҵ�����%s����ȷ���Ѱ�IDACSharp.dll�ŵ�IDA��Ŀ¼�£�\n", "Start");
				return;
			}

			method->Invoke(nullptr, nullptr);
		}

		// ����
		static void Term(){
			MethodInfo^ method = FindMethod("Term");
			if(loaderType == nullptr){
				msg("δ�ҵ�����%s����ȷ���Ѱ�IDACSharp.dll�ŵ�IDA��Ŀ¼�£�\n", "Term");
				return;
			}

			method->Invoke(nullptr, nullptr);
		}

		// ���һ����־
		static void WriteLine(String^ str){
			File::AppendAllText("csharp.log", str);
		}

		static void WriteLine(String^ format, ...array<Object^>^ args){
			WriteLine(String::Format(format + "\r\n", args));
		}
	};

	// ����ӿڡ�
	// ����CSharp���������ʵ�ָýӿڣ�CSharpLoader���ܼ��ز��
	public interface class IPlugin{
		bool Init();
		void Start();
		void Term();

		property String^ Name;
	};
}
