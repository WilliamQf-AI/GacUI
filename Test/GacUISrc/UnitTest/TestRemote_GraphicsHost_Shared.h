#include "TestRemote.h"

using namespace vl::presentation::compositions;
using namespace vl::presentation::controls;

namespace remote_graphics_host_tests
{
	class GraphicsHostProtocol : public SingleScreenProtocol
	{
	public:
		static SingleScreenConfig MakeSingleScreenConfig()
		{
			SingleScreenConfig config;

			config.customFramePadding = { 8,8,8,8 };

			config.fontConfig.defaultFont.fontFamily = L"One";
			config.fontConfig.supportedFonts = Ptr(new List<WString>());
			config.fontConfig.supportedFonts->Add(L"One");
			config.fontConfig.supportedFonts->Add(L"Two");
			config.fontConfig.supportedFonts->Add(L"Three");

			config.screenConfig.bounds = { 0,0,640,480 };
			config.screenConfig.clientBounds = { 0,0,640,440 };
			config.screenConfig.scalingX = 1;
			config.screenConfig.scalingY = 1;

			return config;
		}

		GraphicsHostProtocol()
			: SingleScreenProtocol(MakeSingleScreenConfig())
		{
		}
	};

	class EmptyControlTheme : public theme::ThemeTemplates
	{
	public:
		EmptyControlTheme()
		{
			Name = WString::Unmanaged(L"EmptyControlTheme");
			PreferCustomFrameWindow = true;
			CustomFrameWindow = [](auto)
			{
				auto ct = new templates::GuiWindowTemplate;
				ct->SetMinSizeLimitation(GuiGraphicsComposition::LimitToElementAndChildren);
				ct->SetContainerComposition(ct);
				ct->SetFocusableComposition(ct);
				return ct;
			};
		}
	};

	extern Func<void()>						MakeGuiMain(GraphicsHostProtocol& protocol, List<WString>& eventLogs, GuiWindow*& controlHost);

	void									AttachAndLogEvents(GuiGraphicsComposition* sender, const wchar_t* name, List<WString>& eventLogs);

	NativeWindowKeyInfo						MakeKeyInfo(bool ctrl, bool shift, bool alt, VKEY code);
	NativeWindowCharInfo					MakeCharInfo(bool ctrl, bool shift, bool alt, wchar_t code);
	NativeWindowMouseInfo					MakeMouseInfo(bool left, bool middle, bool right, vint x, vint y, vint wheel);
	remoteprotocol::IOMouseInfoWithButton	MakeMouseInfoWithButton(remoteprotocol::IOMouseButton button, bool left, bool middle, bool right, vint x, vint y, vint wheel);
}
using namespace remote_graphics_host_tests;