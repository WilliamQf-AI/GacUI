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
GuiRemoteEvents
***********************************************************************/

	class GuiRemoteEvents : public Object, public virtual IGuiRemoteProtocolEvents
	{
		friend class GuiRemoteController;
	protected:
		GuiRemoteController*		remote;

	public:
		GuiRemoteEvents(GuiRemoteController* _remote);
		~GuiRemoteEvents();

		// =============================================================
		// IGuiRemoteProtocolEvents
		// =============================================================

		// message

		void	RespondGetFontConfig(vint id, const remoteprotocol::FontConfig& arguments) override;
		void	RespondGetScreenConfig(vint id, const remoteprotocol::ScreenConfig& arguments) override;

		// controlling

		void	OnConnect() override;
		void	OnDisconnect() override;
		void	OnExit() override;

		// system

		void	OnScreenUpdated(const remoteprotocol::ScreenConfig& arguments) override;
	};
}

#endif