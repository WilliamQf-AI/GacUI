﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#ifndef VCZH_WORKFLOW_COMPILER_GENERATED_GUIFAKEDIALOGSERVICEUIREFLECTION
#define VCZH_WORKFLOW_COMPILER_GENERATED_GUIFAKEDIALOGSERVICEUIREFLECTION

#include "GuiFakeDialogServiceUIIncludes.h"
#ifndef VCZH_DEBUG_NO_REFLECTION
#include "../../../../Reflection/TypeDescriptors/GuiReflectionPlugin.h"
#endif

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#endif

/***********************************************************************
Reflection
***********************************************************************/

namespace vl
{
	namespace reflection
	{
		namespace description
		{
#ifndef VCZH_DEBUG_NO_REFLECTION
			DECL_TYPE_INFO(::gaclib_controls::ColorComponentControl)
			DECL_TYPE_INFO(::gaclib_controls::ColorComponentControlConstructor)
			DECL_TYPE_INFO(::gaclib_controls::ColorDialogControl)
			DECL_TYPE_INFO(::gaclib_controls::ColorDialogControlConstructor)
			DECL_TYPE_INFO(::gaclib_controls::ColorDialogWindow)
			DECL_TYPE_INFO(::gaclib_controls::ColorDialogWindowConstructor)
			DECL_TYPE_INFO(::gaclib_controls::DialogStrings)
			DECL_TYPE_INFO(::gaclib_controls::FileDialogWindow)
			DECL_TYPE_INFO(::gaclib_controls::FileDialogWindowConstructor)
			DECL_TYPE_INFO(::gaclib_controls::FilePickerControl)
			DECL_TYPE_INFO(::gaclib_controls::FilePickerControlConstructor)
			DECL_TYPE_INFO(::gaclib_controls::FontNameControl)
			DECL_TYPE_INFO(::gaclib_controls::FontNameControlConstructor)
			DECL_TYPE_INFO(::gaclib_controls::FontSizeControl)
			DECL_TYPE_INFO(::gaclib_controls::FontSizeControlConstructor)
			DECL_TYPE_INFO(::gaclib_controls::FullFontDialogWindow)
			DECL_TYPE_INFO(::gaclib_controls::FullFontDialogWindowConstructor)
			DECL_TYPE_INFO(::gaclib_controls::IDialogStringsStrings)
			DECL_TYPE_INFO(::gaclib_controls::MessageBoxButtonTemplate)
			DECL_TYPE_INFO(::gaclib_controls::MessageBoxButtonTemplateConstructor)
			DECL_TYPE_INFO(::gaclib_controls::MessageBoxWindow)
			DECL_TYPE_INFO(::gaclib_controls::MessageBoxWindowConstructor)
			DECL_TYPE_INFO(::gaclib_controls::SimpleFontDialogWindow)
			DECL_TYPE_INFO(::gaclib_controls::SimpleFontDialogWindowConstructor)

#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA

			BEGIN_INTERFACE_PROXY_NOPARENT_SHAREDPTR(::gaclib_controls::IDialogStringsStrings)
				::vl::WString Abort() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Abort);
				}
				::vl::WString Blue() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Blue);
				}
				::vl::WString Bold() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Bold);
				}
				::vl::WString Cancel() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Cancel);
				}
				::vl::WString Color() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Color);
				}
				::vl::WString ColorDialogTitle() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(ColorDialogTitle);
				}
				::vl::WString Continue() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Continue);
				}
				::vl::WString FileDialogAskCreateFile() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogAskCreateFile);
				}
				::vl::WString FileDialogAskOverrideFile() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogAskOverrideFile);
				}
				::vl::WString FileDialogErrorEmptySelection() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogErrorEmptySelection);
				}
				::vl::WString FileDialogErrorFileExpected() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogErrorFileExpected);
				}
				::vl::WString FileDialogErrorFileNotExist() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogErrorFileNotExist);
				}
				::vl::WString FileDialogErrorFolderNotExist() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogErrorFolderNotExist);
				}
				::vl::WString FileDialogErrorMultipleSelectionNotEnabled() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogErrorMultipleSelectionNotEnabled);
				}
				::vl::WString FileDialogFileName() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogFileName);
				}
				::vl::WString FileDialogOpen() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogOpen);
				}
				::vl::WString FileDialogSave() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogSave);
				}
				::vl::WString FileDialogTextLoadingFiles() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogTextLoadingFiles);
				}
				::vl::WString FileDialogTextLoadingFolders() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FileDialogTextLoadingFolders);
				}
				::vl::WString FontColorGroup() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontColorGroup);
				}
				::vl::WString FontColorGroup2() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontColorGroup2);
				}
				::vl::WString FontDialogTitle() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontDialogTitle);
				}
				::vl::WString FontEffectGroup() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontEffectGroup);
				}
				::vl::WString FontNameGroup() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontNameGroup);
				}
				::vl::WString FontPreviewGroup() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontPreviewGroup);
				}
				::vl::WString FontSizeGroup() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(FontSizeGroup);
				}
				::vl::WString Green() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Green);
				}
				::vl::WString HAA() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(HAA);
				}
				::vl::WString Ignore() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Ignore);
				}
				::vl::WString Italic() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Italic);
				}
				::vl::WString No() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(No);
				}
				::vl::WString OK() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(OK);
				}
				::vl::WString Red() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Red);
				}
				::vl::WString Retry() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Retry);
				}
				::vl::WString Strikeline() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Strikeline);
				}
				::vl::WString TryAgain() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(TryAgain);
				}
				::vl::WString Underline() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Underline);
				}
				::vl::WString VAA() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(VAA);
				}
				::vl::WString Yes() override
				{
					INVOKEGET_INTERFACE_PROXY_NOPARAMS(Yes);
				}
			END_INTERFACE_PROXY(::gaclib_controls::IDialogStringsStrings)
#endif
#endif

			extern bool LoadGuiFakeDialogServiceUITypes();
		}
	}
}

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif
