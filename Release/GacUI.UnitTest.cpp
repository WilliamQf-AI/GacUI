﻿/***********************************************************************
THIS FILE IS AUTOMATICALLY GENERATED. DO NOT MODIFY
DEVELOPER: Zihan Chen(vczh)
***********************************************************************/
#include "GacUI.UnitTest.h"

/***********************************************************************
.\GUIUNITTESTUTILITIES.CPP
***********************************************************************/

using namespace vl;

namespace vl::presentation::unittest
{
}

Func<void()> guiMainProxy;

void SetGuiMainProxy(const Func<void()>& proxy)
{
	guiMainProxy = proxy;
}

void GuiMain()
{
	guiMainProxy();
}
