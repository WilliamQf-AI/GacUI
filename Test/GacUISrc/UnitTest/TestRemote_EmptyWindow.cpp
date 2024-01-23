#include "TestRemote.h"

class EmptyWindowProtocol : public NotImplementedProtocolBase
{
public:
	static EmptyWindowProtocol*	instance;

	Func<void()>				processRemoteEvents;
	bool						connectionEstablished = false;
	bool						connectionStopped = false;
	WindowSizingConfig			sizingConfig;

	EmptyWindowProtocol(Func<void()> _processRemoteEvents)
		: processRemoteEvents(_processRemoteEvents)
	{
		CHECK_ERROR(instance == nullptr, L"EmptyWindowProtocol can only have one instance");
		instance = this;

		sizingConfig.bounds = { 0,0,0,0 };
		sizingConfig.clientBounds = { 0,0,0,0 };
		sizingConfig.customFramePadding = { 8,8,8,8 };
	}

	~EmptyWindowProtocol()
	{
		instance = nullptr;
	}

	void Submit() override
	{
		CHECK_ERROR(!connectionStopped, L"IGuiRemoteProtocol::Submit is not allowed to call after connection stopped.");
	}

	void ProcessRemoteEvents() override
	{
		processRemoteEvents();
	}

	WString GetExecutablePath() override
	{
		return L"/EmptyWindow/Protocol.exe";
	}

	void RequestControllerGetFontConfig(vint id) override
	{
		FontConfig response;
		response.defaultFont.fontFamily = L"One";
		response.supportedFonts = Ptr(new List<WString>());
		response.supportedFonts->Add(L"One");
		response.supportedFonts->Add(L"Two");
		response.supportedFonts->Add(L"Three");
		events->RespondControllerGetFontConfig(id, response);
	}

	void RequestControllerGetScreenConfig(vint id) override
	{
		ScreenConfig response;
		response.bounds = { 0,0,640,480};
		response.clientBounds = { 0,0,640,440 };
		response.scalingX = 1;
		response.scalingY = 1;
		events->RespondControllerGetScreenConfig(id, response);
	}

	void RequestControllerConnectionEstablished() override
	{
		CHECK_ERROR(!connectionEstablished, L"IGuiRemoteProtocol::RequestControllerConnectionEstablished is not allowed to call twice.");
		connectionEstablished = true;
	}

	void RequestControllerConnectionStopped() override
	{
		CHECK_ERROR(!connectionStopped, L"IGuiRemoteProtocol::RequestControllerConnectionStopped is not allowed to call twice.");
		connectionStopped = true;
	}

	void RequestWindowGetBounds(vint id) override
	{
		events->RespondWindowGetBounds(id, sizingConfig);
	}

	void RequestWindowNotifySetTitle(const ::vl::WString& arguments) override
	{
	}

	void RequestWindowNotifySetEnabled(const bool& arguments) override
	{
	}

	void RequestWindowNotifySetTopMost(const bool& arguments) override
	{
	}

	void RequestWindowNotifySetShowInTaskBar(const bool& arguments) override
	{
	}

	void RequestWindowNotifySetBounds(const NativeRect& arguments) override
	{
		sizingConfig.bounds = arguments;
		sizingConfig.clientBounds = sizingConfig.bounds;
		events->OnWindowBoundsUpdated(sizingConfig);
	}

	void RequestWindowNotifySetClientSize(const NativeSize& arguments) override
	{
		sizingConfig.bounds = { sizingConfig.bounds.LeftTop(), arguments };
		sizingConfig.clientBounds = sizingConfig.bounds;
		events->OnWindowBoundsUpdated(sizingConfig);
	}

	void RequestWindowNotifySetCustomFrameMode(const bool& arguments) override {}
	void RequestWindowNotifySetMaximizedBox(const bool& arguments) override {}
	void RequestWindowNotifySetMinimizedBox(const bool& arguments) override {}
	void RequestWindowNotifySetBorder(const bool& arguments) override {}
	void RequestWindowNotifySetSizeBox(const bool& arguments) override {}
	void RequestWindowNotifySetIconVisible(const bool& arguments) override {}
	void RequestWindowNotifySetTitleBar(const bool& arguments) override {}
	void RequestWindowNotifyActivate() override {}

	void RequestWindowNotifyShow(const WindowShowing& arguments) override
	{
		sizingConfig.sizeState = arguments.sizeState;
	}
};
EmptyWindowProtocol* EmptyWindowProtocol::instance = nullptr;

TEST_FILE
{
	TEST_CATEGORY(L"Create one window and exit immediately")
	{
		EmptyWindowProtocol protocol([]()
		{
			auto window = GetCurrentController()->WindowService()->GetMainWindow();
			TEST_ASSERT(window);
			TEST_ASSERT(window->GetBounds() == NativeRect(0, 0, 100, 200));
			TEST_ASSERT(window->GetClientSize() == NativeSize(100, 200));
			TEST_ASSERT(EmptyWindowProtocol::instance->sizingConfig.bounds == NativeRect(270, 120, 370, 320));
			TEST_ASSERT(EmptyWindowProtocol::instance->sizingConfig.clientBounds == NativeRect(270, 120, 370, 320));
			window->Hide(true);
		});
		SetGuiMainProxy([]()
		{
			TEST_CASE(L"Establish connection")
			{
				TEST_ASSERT(!EmptyWindowProtocol::instance->connectionEstablished);
				EmptyWindowProtocol::instance->events->OnControllerConnect();
				TEST_ASSERT(EmptyWindowProtocol::instance->connectionEstablished);
			});

			TEST_CASE(L"Create and destroy a window")
			{
				auto ws = GetCurrentController()->WindowService();
				auto window = ws->CreateNativeWindow(INativeWindow::Normal);
				window->SetTitle(L"EmptyWindow");
				window->SetClientSize({ 100,200 });
				ws->Run(window);
			});
		});
		BatchedProtocol batchedProtocol(&protocol);
		SetupRemoteNativeController(&batchedProtocol);
		SetGuiMainProxy(nullptr);

		TEST_CASE(L"Ensure stopped")
		{
			TEST_ASSERT(EmptyWindowProtocol::instance->connectionStopped);
		});
	});

	TEST_CATEGORY(L"Close a window")
	{
		LoggingWindowListener listener;
		EmptyWindowProtocol protocol([&]()
		{
			listener.AssertCallbacks(
				L"Opened()",
				L"GotFocus()",
				L"RenderingAsActivated()"
			);
			auto window = GetCurrentController()->WindowService()->GetMainWindow();
			window->Hide(true);
			listener.AssertCallbacks(
				L"BeforeClosing()",
				L"AfterClosing()",
				L"BeforeClosing()",
				L"AfterClosing()",
				L"LostFocus()",
				L"RenderingAsDeactivated()",
				L"Closed()"
			);
		});
		SetGuiMainProxy([]()
		{
			EmptyWindowProtocol::instance->events->OnControllerConnect();
			TEST_CASE(L"Create and close a window")
			{
				auto ws = GetCurrentController()->WindowService();
				auto window = ws->CreateNativeWindow(INativeWindow::Normal);
				window->InstallListener(&listener);
				window->SetTitle(L"EmptyWindow");
				ws->Run(window);
				listener.AssertCallbacks(
					L"Destroying()",
					L"Destroyed()"
				);
			});
		});
		BatchedProtocol batchedProtocol(&protocol);
		SetupRemoteNativeController(&batchedProtocol);
		SetGuiMainProxy(nullptr);
	});

	TEST_CATEGORY(L"Block closing a window")
	{
		LoggingWindowListener listener;
		EmptyWindowProtocol protocol([&]()
		{
			auto window = GetCurrentController()->WindowService()->GetMainWindow();
			// TODO: test before closing on main and non-main window, setting cancel to different values and expect to run only once
			window->Hide(true);
		});
		SetGuiMainProxy([]()
		{
			EmptyWindowProtocol::instance->events->OnControllerConnect();
			TEST_CASE(L"Create and block closing a window")
			{
				auto ws = GetCurrentController()->WindowService();
				auto window = ws->CreateNativeWindow(INativeWindow::Normal);
				window->InstallListener(&listener);
				ws->Run(window);
			});
		});
		BatchedProtocol batchedProtocol(&protocol);
		SetupRemoteNativeController(&batchedProtocol);
		SetGuiMainProxy(nullptr);
	});

	// TODO: test ControllerRequestExit with success and blocked
	// TODO: test ControllerForceExit and ensure it skipped INativeWindowListener::(Before|After)Closing
	// TODO: test ControllerDisconnect and ControllerConnect
	// TODO: test enabled/activate/showactivated from INativeWindow and event (bidirectional controlling)
	// TODO: test size status from INativeWindow and event (bidirectional controlling)
}