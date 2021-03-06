using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// 有关程序集的常规信息通过下列属性集
// 控制。更改这些属性值可修改
// 与程序集关联的信息。
//
[assembly:AssemblyTitleAttribute("IDACSharp")];
[assembly:AssemblyDescriptionAttribute("这是一个IDACSharp插件，用于向C#提供IDA函数接口，以方便使用C#开发IDA插件")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("新生命开发团队")];
[assembly:AssemblyProductAttribute("IDACSharp")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) 新生命开发团队 2002-2011")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// 程序集的版本信息由下面四个值组成:
//
//      主版本
//      次版本
//      内部版本号
//      修订号
//
// 您可以指定所有值，也可使用“修订号”和“内部版本号”的默认值，
// 方法是按如下所示使用“*”:

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];

[assembly:AssemblyVersionAttribute("1.1.*")];
[assembly:AssemblyFileVersionAttribute("1.1.2011.0424")];

/*
 *
 * v1.1.2011.0424	小曾增加一些调试相关封装
 *
 * V1.0.2010.0519	完成常用函数的封装
 */