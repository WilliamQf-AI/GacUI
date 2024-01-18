/***********************************************************************
This file is generated by: Vczh Parser Generator
From parser definition:GuiRemoteProtocol
Licensed under https://github.com/vczh-libraries/License
***********************************************************************/

#ifndef VCZH_PRESENTATION_REMOTEPROTOCOL_LEXER
#define VCZH_PRESENTATION_REMOTEPROTOCOL_LEXER

#include <VlppGlrParser.h>

namespace vl::presentation::remoteprotocol
{
	enum class GuiRemoteProtocolTokens : vl::vint32_t
	{
		TYPE = 0,
		PROTOCOL = 1,
		REQUEST = 2,
		RESPONSE = 3,
		VOID = 4,
		BOOLEAN = 5,
		INTEGER = 6,
		FLOAT = 7,
		DOUBLE = 8,
		STRING = 9,
		CPP_NAME = 10,
		NAME = 11,
		OPEN_BRACE = 12,
		CLOSE_BRACE = 13,
		COLON = 14,
		SEMICOLON = 15,
		SPACE = 16,
	};

	constexpr vl::vint GuiRemoteProtocolTokenCount = 17;
	extern bool GuiRemoteProtocolTokenDeleter(vl::vint token);
	extern const wchar_t* GuiRemoteProtocolTokenId(GuiRemoteProtocolTokens token);
	extern const wchar_t* GuiRemoteProtocolTokenDisplayText(GuiRemoteProtocolTokens token);
	extern const wchar_t* GuiRemoteProtocolTokenRegex(GuiRemoteProtocolTokens token);
	extern void GuiRemoteProtocolLexerData(vl::stream::IStream& outputStream);
}
#endif