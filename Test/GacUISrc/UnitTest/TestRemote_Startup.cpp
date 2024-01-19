#include "../../../Source/GacUI.h"
#include "../../../Source/PlatformProviders/Remote/GuiRemoteController.h"

extern void SetGuiMainProxy(void(*proxy)());

using namespace vl;
using namespace vl::collections;
using namespace vl::presentation;
using namespace vl::presentation::remoteprotocol;

class StartUpProtocol : public Object, public IGuiRemoteProtocol
{
public:
	static StartUpProtocol*		instance;
	IGuiRemoteProtocolEvents*	events = nullptr;

	StartUpProtocol()
	{
		CHECK_ERROR(instance == nullptr, L"StartUpProtocol can only have one instance");
		instance = this;
	}

	~StartUpProtocol()
	{
		instance = nullptr;
	}

	void Initialize(IGuiRemoteProtocolEvents* _events) override
	{
		events = _events;
	}

	void Submit() override
	{
		// respond to messages immediately in this test
		// no need to submit
	}

	WString GetExecutablePath() override
	{
		return L"/StartUp/Protocol.exe";
	}

	void RequestControllerGetFontConfig(vint id) override
	{
		FontConfig response;
		response.defaultFont.fontFamily = L"StartUpDefault";
		response.defaultFont.bold = true;
		response.supportedFonts = Ptr(new List<WString>());
		response.supportedFonts->Add(L"StartUpDefault");
		response.supportedFonts->Add(L"Another");
		response.supportedFonts->Add(L"YetAnother");
		events->RespondControllerGetFontConfig(id, response);
	}

	void RequestControllerGetScreenConfig(vint id) override
	{
		ScreenConfig response;
		response.bounds = { 0,0,30,20 };
		response.clientBounds = { 1,1,29,19 };
		response.scalingX = 1;
		response.scalingY = 1;
		events->RespondControllerGetScreenConfig(id, response);
	}

	void RequestControllerConnectionEstablished() override
	{
	}

	void RequestWindowGetBounds(vint id) override
	{
		NativeRect response = { 0,0,50,40 };
		events->RespondWindowGetBounds(id, response);
	}
};
StartUpProtocol* StartUpProtocol::instance = nullptr;

TEST_FILE
{
	TEST_CATEGORY(L"Start and Stop")
	{
		StartUpProtocol protocol;
		SetGuiMainProxy([]()
		{
			StartUpProtocol::instance->events->OnControllerConnect();

			auto rs = GetCurrentController()->ResourceService();
			auto ss = GetCurrentController()->ScreenService();

			TEST_CASE(L"Assert font config")
			{
				TEST_ASSERT(GetCurrentController()->GetExecutablePath() == L"/StartUp/Protocol.exe");
				TEST_ASSERT(rs->GetDefaultFont().fontFamily == L"StartUpDefault");
				TEST_ASSERT(rs->GetDefaultFont().bold == true);
				TEST_ASSERT(rs->GetDefaultFont().italic == false);

				List<WString> fonts;
				rs->EnumerateFonts(fonts);
				TEST_ASSERT(fonts.Count() == 3);
				TEST_ASSERT(fonts[0] == L"StartUpDefault");
				TEST_ASSERT(fonts[1] == L"Another");
				TEST_ASSERT(fonts[2] == L"YetAnother");
			});

			TEST_CASE(L"Assert screen config")
			{
				TEST_ASSERT(ss->GetScreenCount() == 1);
				auto screen = ss->GetScreen(0);
				TEST_ASSERT(screen->IsPrimary() == true);
				TEST_ASSERT(screen->GetBounds() == NativeRect(0, 0, 50, 40));
				TEST_ASSERT(screen->GetClientBounds() == NativeRect(0, 0, 50, 40));
				TEST_ASSERT(screen->GetScalingX() == 1);
				TEST_ASSERT(screen->GetScalingY() == 1);
			});

			TEST_CASE(L"Assert updated screen config")
			{
				{
					ScreenConfig response;
					response.bounds = { 1,1,19, 29 };
					response.clientBounds = { 2,2,18,28 };
					response.scalingX = 1.2;
					response.scalingY = 1.5;
					StartUpProtocol::instance->events->OnControllerScreenUpdated(response);
				}
				TEST_ASSERT(ss->GetScreenCount() == 1);
				auto screen = ss->GetScreen(0);
				TEST_ASSERT(screen->IsPrimary() == true);
				TEST_ASSERT(screen->GetBounds() == NativeRect(0, 0, 50, 40));
				TEST_ASSERT(screen->GetClientBounds() == NativeRect(0, 0, 50, 40));
				TEST_ASSERT(screen->GetScalingX() == 1.2);
				TEST_ASSERT(screen->GetScalingY() == 1.5);
			});

			StartUpProtocol::instance->events->OnControllerDisconnect();
			StartUpProtocol::instance->events->OnControllerExit();
		});
		SetupRemoteNativeController(&protocol);
		SetGuiMainProxy(nullptr);
	});
	
	TEST_CATEGORY(L"Create one window and exit immediately")
	{
		StartUpProtocol protocol;
		SetGuiMainProxy([]()
		{
		});
		SetupRemoteNativeController(&protocol);
		SetGuiMainProxy(nullptr);
	});
}