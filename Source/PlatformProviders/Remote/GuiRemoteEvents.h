/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
GacUI::Remote Window

Interfaces:
  GuiRemoteEvent

***********************************************************************/

#ifndef VCZH_PRESENTATION_GUIREMOTECONTROLLER_GUIREMOTEEVENT
#define VCZH_PRESENTATION_GUIREMOTECONTROLLER_GUIREMOTEEVENT

#include "../../Utilities/SharedServices/GuiSharedCallbackService.h"
#include "../../Utilities/SharedServices/GuiSharedAsyncService.h"
#include "GuiRemoteProtocol.h"

namespace vl::presentation
{
	class GuiRemoteController;

/***********************************************************************
GuiRemoteMessages
***********************************************************************/

	class GuiRemoteMessages : public Object
	{
		friend class GuiRemoteController;
	protected:
		GuiRemoteController*						remote;
		vint										id = 0;

#define MESSAGE_NORES(NAME, RESPONSE)
#define MESSAGE_RES(NAME, RESPONSE)										collections::Dictionary<vint, RESPONSE> response ## NAME;
#define MESSAGE_HANDLER(NAME, REQUEST, RESPONSE, REQTAG, RESTAG, ...)	MESSAGE_ ## RESTAG(NAME, RESPONSE)
		GACUI_REMOTEPROTOCOL_MESSAGES(MESSAGE_HANDLER)
#undef MESSAGE_HANDLER
#undef MESSAGE_RES
#undef MESSAGE_NORES

	public:
		GuiRemoteMessages(GuiRemoteController* _remote);
		~GuiRemoteMessages();

		void	Submit();
		void	ClearResponses();

		// messages

#define MESSAGE_NOREQ_NORES(NAME, REQUEST, RESPONSE)					void Request ## NAME();
#define MESSAGE_NOREQ_RES(NAME, REQUEST, RESPONSE)						vint Request ## NAME();
#define MESSAGE_REQ_NORES(NAME, REQUEST, RESPONSE)						void Request ## NAME(const REQUEST& arguments);
#define MESSAGE_REQ_RES(NAME, REQUEST, RESPONSE)						vint Request ## NAME(const REQUEST& arguments);
#define MESSAGE_HANDLER(NAME, REQUEST, RESPONSE, REQTAG, RESTAG, ...)	MESSAGE_ ## REQTAG ## _ ## RESTAG(NAME, REQUEST, RESPONSE)
		GACUI_REMOTEPROTOCOL_MESSAGES(MESSAGE_HANDLER)
#undef MESSAGE_HANDLER
#undef MESSAGE_REQ_RES
#undef MESSAGE_REQ_NORES
#undef MESSAGE_NOREQ_RES
#undef MESSAGE_NOREQ_NORES

#define MESSAGE_NORES(NAME, RESPONSE)
#define MESSAGE_RES(NAME, RESPONSE)\
		void Respond ## NAME(vint id, const RESPONSE& arguments);\
		const RESPONSE& Retrieve ## NAME(vint id);\

#define MESSAGE_HANDLER(NAME, REQUEST, RESPONSE, REQTAG, RESTAG, ...)	MESSAGE_ ## RESTAG(NAME, RESPONSE)
			GACUI_REMOTEPROTOCOL_MESSAGES(MESSAGE_HANDLER)
#undef MESSAGE_HANDLER
#undef MESSAGE_RES
#undef MESSAGE_NORES
	};

/***********************************************************************
GuiRemoteEvents
***********************************************************************/

	class GuiRemoteEvents : public Object, public virtual IGuiRemoteProtocolEvents
	{
		friend class GuiRemoteController;
	protected:
		GuiRemoteController*						remote;

	public:
		GuiRemoteEvents(GuiRemoteController* _remote);
		~GuiRemoteEvents();

		// =============================================================
		// IGuiRemoteProtocolEvents
		// =============================================================

		// messages

#define MESSAGE_NORES(NAME, RESPONSE)
#define MESSAGE_RES(NAME, RESPONSE)										void Respond ## NAME(vint id, const RESPONSE& arguments) override;
#define MESSAGE_HANDLER(NAME, REQUEST, RESPONSE, REQTAG, RESTAG, ...)	MESSAGE_ ## RESTAG(NAME, RESPONSE)
		GACUI_REMOTEPROTOCOL_MESSAGES(MESSAGE_HANDLER)
#undef MESSAGE_HANDLER
#undef MESSAGE_RES
#undef MESSAGE_NORES

		void	ClearResponses();

		// events

		void	OnControllerConnect() override;
		void	OnControllerDisconnect() override;
		void	OnControllerRequestExit() override;
		void	OnControllerForceExit() override;
		void	OnControllerScreenUpdated(const remoteprotocol::ScreenConfig& arguments) override;

		void	OnWindowBoundsUpdated(const remoteprotocol::WindowSizingConfig& arguments) override;
	};
}

#endif