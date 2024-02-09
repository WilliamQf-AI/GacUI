/***********************************************************************
This file is generated by : Vczh GacUI Remote Protocol Generator
Licensed under https ://github.com/vczh-libraries/License
***********************************************************************/

#ifndef VCZH_PRESENTATION_GUIREMOTECONTROLLER_REMOTEPROTOCOLSCHEMA
#define VCZH_PRESENTATION_GUIREMOTECONTROLLER_REMOTEPROTOCOLSCHEMA

#include "../../GuiRemoteProtocolSchemaShared.h"

namespace vl::presentation::remoteprotocol
{
	enum class IOMouseButton
	{
		Left,
		Middle,
		Right,
	};

	enum class RendererType
	{
		FocusRectangle,
		SolidBorder,
		SinkBorder,
		SinkSplitter,
		SolidBackground,
		GradientBackground,
		InnerShadow,
		SolidLabel,
		Polygon,
		UnsupportedImageFrame,
		UnsupportedColorizedText,
		UnsupportedDocument,
	};

	enum class ElementHorizontalAlignment
	{
		Left,
		Right,
		Center,
	};

	enum class ElementVerticalAlignment
	{
		Top,
		Bottom,
		Center,
	};

	enum class ElementSolidLabelMeasuringRequest
	{
		FontHeight,
		TotalSize,
	};

	struct FontConfig
	{
		::vl::presentation::FontProperties defaultFont;
		::vl::Ptr<::vl::collections::List<::vl::WString>> supportedFonts;
	};

	struct ScreenConfig
	{
		::vl::presentation::NativeRect bounds;
		::vl::presentation::NativeRect clientBounds;
		double scalingX;
		double scalingY;
	};

	struct IOMouseInfoWithButton
	{
		::vl::presentation::remoteprotocol::IOMouseButton button;
		::vl::presentation::NativeWindowMouseInfo info;
	};

	struct GlobalShortcutKey
	{
		::vl::vint id;
		bool ctrl;
		bool shift;
		bool alt;
		::vl::presentation::VKEY code;
	};

	struct WindowSizingConfig
	{
		::vl::presentation::NativeRect bounds;
		::vl::presentation::NativeRect clientBounds;
		::vl::presentation::INativeWindow::WindowSizeState sizeState;
		::vl::presentation::NativeMargin customFramePadding;
	};

	struct WindowShowing
	{
		bool activate;
		::vl::presentation::INativeWindow::WindowSizeState sizeState;
	};

	struct ElementDesc_SolidBorder
	{
		::vl::vint id;
		::vl::presentation::Color borderColor;
		::vl::presentation::elements::ElementShape shape;
	};

	struct ElementDesc_SinkBorder
	{
		::vl::vint id;
		::vl::presentation::Color leftTopColor;
		::vl::presentation::Color rightBottomColor;
	};

	struct ElementDesc_SinkSplitter
	{
		::vl::vint id;
		::vl::presentation::Color leftTopColor;
		::vl::presentation::Color rightBottomColor;
		::vl::presentation::elements::Gui3DSplitterElement::Direction direction;
	};

	struct ElementDesc_SolidBackground
	{
		::vl::vint id;
		::vl::presentation::Color backgroundColor;
		::vl::presentation::elements::ElementShape shape;
	};

	struct ElementDesc_GradientBackground
	{
		::vl::vint id;
		::vl::presentation::Color leftTopColor;
		::vl::presentation::Color rightBottomColor;
		::vl::presentation::elements::GuiGradientBackgroundElement::Direction direction;
		::vl::presentation::elements::ElementShape shape;
	};

	struct ElementDesc_InnerShadow
	{
		::vl::vint id;
		::vl::presentation::Color shadowColor;
		::vl::vint thickness;
	};

	struct ElementDesc_Polygon
	{
		::vl::vint id;
		::vl::presentation::Size size;
		::vl::presentation::Color borderColor;
		::vl::presentation::Color backgroundColor;
		::vl::Ptr<::vl::collections::List<::vl::presentation::Point>> points;
	};

	struct ElementDesc_SolidLabel
	{
		::vl::vint id;
		::vl::presentation::Color textColor;
		::vl::presentation::remoteprotocol::ElementHorizontalAlignment horizontalAlignment;
		::vl::presentation::remoteprotocol::ElementVerticalAlignment verticalAlignment;
		bool wrapLine;
		bool wrapLineHeightCalculation;
		bool ellipse;
		bool multiline;
		::vl::Nullable<::vl::presentation::FontProperties> font;
		::vl::Nullable<::vl::WString> text;
		::vl::Nullable<::vl::presentation::remoteprotocol::ElementSolidLabelMeasuringRequest> measuringRequest;
	};

	struct RendererCreation
	{
		::vl::vint id;
		::vl::presentation::remoteprotocol::RendererType type;
	};

	struct ElementMeasuring_FontHeight
	{
		::vl::WString fontFamily;
		::vl::vint fontSize;
		::vl::vint height;
	};

	struct ElementMeasuring_ElementMinSize
	{
		::vl::vint id;
		::vl::presentation::Size minSize;
	};

	struct ElementMeasurings
	{
		::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::ElementMeasuring_FontHeight>> fontHeights;
		::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::ElementMeasuring_ElementMinSize>> minSizes;
	};

	struct ElementRendering
	{
		::vl::vint id;
		::vl::presentation::Rect bounds;
		::vl::presentation::Rect clipper;
	};

	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::IOMouseButton>(const ::vl::presentation::remoteprotocol::IOMouseButton & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::INativeWindowListener::HitTestResult>(const ::vl::presentation::INativeWindowListener::HitTestResult & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::INativeCursor::SystemCursorType>(const ::vl::presentation::INativeCursor::SystemCursorType & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::INativeWindow::WindowSizeState>(const ::vl::presentation::INativeWindow::WindowSizeState & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::RendererType>(const ::vl::presentation::remoteprotocol::RendererType & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::elements::ElementShapeType>(const ::vl::presentation::elements::ElementShapeType & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::elements::GuiGradientBackgroundElement::Direction>(const ::vl::presentation::elements::GuiGradientBackgroundElement::Direction & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::elements::Gui3DSplitterElement::Direction>(const ::vl::presentation::elements::Gui3DSplitterElement::Direction & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementHorizontalAlignment>(const ::vl::presentation::remoteprotocol::ElementHorizontalAlignment & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementVerticalAlignment>(const ::vl::presentation::remoteprotocol::ElementVerticalAlignment & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementSolidLabelMeasuringRequest>(const ::vl::presentation::remoteprotocol::ElementSolidLabelMeasuringRequest & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeCoordinate>(const ::vl::presentation::NativeCoordinate & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativePoint>(const ::vl::presentation::NativePoint & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeSize>(const ::vl::presentation::NativeSize & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeRect>(const ::vl::presentation::NativeRect & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeMargin>(const ::vl::presentation::NativeMargin & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::Point>(const ::vl::presentation::Point & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::Size>(const ::vl::presentation::Size & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::Rect>(const ::vl::presentation::Rect & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::FontProperties>(const ::vl::presentation::FontProperties & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::FontConfig>(const ::vl::presentation::remoteprotocol::FontConfig & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ScreenConfig>(const ::vl::presentation::remoteprotocol::ScreenConfig & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeWindowMouseInfo>(const ::vl::presentation::NativeWindowMouseInfo & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::IOMouseInfoWithButton>(const ::vl::presentation::remoteprotocol::IOMouseInfoWithButton & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeWindowKeyInfo>(const ::vl::presentation::NativeWindowKeyInfo & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::NativeWindowCharInfo>(const ::vl::presentation::NativeWindowCharInfo & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::GlobalShortcutKey>(const ::vl::presentation::remoteprotocol::GlobalShortcutKey & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::WindowSizingConfig>(const ::vl::presentation::remoteprotocol::WindowSizingConfig & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::WindowShowing>(const ::vl::presentation::remoteprotocol::WindowShowing & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::elements::ElementShape>(const ::vl::presentation::elements::ElementShape & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_SolidBorder>(const ::vl::presentation::remoteprotocol::ElementDesc_SolidBorder & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_SinkBorder>(const ::vl::presentation::remoteprotocol::ElementDesc_SinkBorder & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter>(const ::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_SolidBackground>(const ::vl::presentation::remoteprotocol::ElementDesc_SolidBackground & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_GradientBackground>(const ::vl::presentation::remoteprotocol::ElementDesc_GradientBackground & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_InnerShadow>(const ::vl::presentation::remoteprotocol::ElementDesc_InnerShadow & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_Polygon>(const ::vl::presentation::remoteprotocol::ElementDesc_Polygon & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementDesc_SolidLabel>(const ::vl::presentation::remoteprotocol::ElementDesc_SolidLabel & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::RendererCreation>(const ::vl::presentation::remoteprotocol::RendererCreation & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementMeasuring_FontHeight>(const ::vl::presentation::remoteprotocol::ElementMeasuring_FontHeight & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementMeasuring_ElementMinSize>(const ::vl::presentation::remoteprotocol::ElementMeasuring_ElementMinSize & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementMeasurings>(const ::vl::presentation::remoteprotocol::ElementMeasurings & value);
	template<> vl::Ptr<vl::glr::json::JsonNode> ConvertCustomTypeToJson<::vl::presentation::remoteprotocol::ElementRendering>(const ::vl::presentation::remoteprotocol::ElementRendering & value);

	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::IOMouseButton>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::IOMouseButton& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::INativeWindowListener::HitTestResult>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::INativeWindowListener::HitTestResult& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::INativeCursor::SystemCursorType>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::INativeCursor::SystemCursorType& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::INativeWindow::WindowSizeState>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::INativeWindow::WindowSizeState& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::RendererType>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::RendererType& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::elements::ElementShapeType>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::elements::ElementShapeType& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::elements::GuiGradientBackgroundElement::Direction>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::elements::GuiGradientBackgroundElement::Direction& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::elements::Gui3DSplitterElement::Direction>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::elements::Gui3DSplitterElement::Direction& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementHorizontalAlignment>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementHorizontalAlignment& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementVerticalAlignment>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementVerticalAlignment& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementSolidLabelMeasuringRequest>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementSolidLabelMeasuringRequest& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeCoordinate>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeCoordinate& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativePoint>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativePoint& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeSize>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeSize& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeRect>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeRect& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeMargin>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeMargin& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::Point>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::Point& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::Size>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::Size& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::Rect>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::Rect& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::FontProperties>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::FontProperties& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::FontConfig>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::FontConfig& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ScreenConfig>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ScreenConfig& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeWindowMouseInfo>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeWindowMouseInfo& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::IOMouseInfoWithButton>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::IOMouseInfoWithButton& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeWindowKeyInfo>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeWindowKeyInfo& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::NativeWindowCharInfo>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::NativeWindowCharInfo& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::GlobalShortcutKey>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::GlobalShortcutKey& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::WindowSizingConfig>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::WindowSizingConfig& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::WindowShowing>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::WindowShowing& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::elements::ElementShape>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::elements::ElementShape& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_SolidBorder>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_SolidBorder& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_SinkBorder>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_SinkBorder& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_SolidBackground>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_SolidBackground& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_GradientBackground>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_GradientBackground& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_InnerShadow>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_InnerShadow& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_Polygon>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_Polygon& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementDesc_SolidLabel>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementDesc_SolidLabel& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::RendererCreation>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::RendererCreation& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementMeasuring_FontHeight>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementMeasuring_FontHeight& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementMeasuring_ElementMinSize>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementMeasuring_ElementMinSize& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementMeasurings>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementMeasurings& value);
	template<> void ConvertJsonToCustomType<::vl::presentation::remoteprotocol::ElementRendering>(vl::Ptr<vl::glr::json::JsonNode> node, ::vl::presentation::remoteprotocol::ElementRendering& value);

#define GACUI_REMOTEPROTOCOL_MESSAGES(HANDLER)\
	HANDLER(ControllerGetFontConfig, void, ::vl::presentation::remoteprotocol::FontConfig, NOREQ, RES, NODROP)\
	HANDLER(ControllerGetScreenConfig, void, ::vl::presentation::remoteprotocol::ScreenConfig, NOREQ, RES, NODROP)\
	HANDLER(ControllerConnectionEstablished, void, void, NOREQ, NORES, NODROP)\
	HANDLER(ControllerConnectionStopped, void, void, NOREQ, NORES, NODROP)\
	HANDLER(IOUpdateGlobalShortcutKey, ::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::GlobalShortcutKey>>, void, REQ, NORES, NODROP)\
	HANDLER(IORequireCapture, void, void, NOREQ, NORES, NODROP)\
	HANDLER(IOReleaseCapture, void, void, NOREQ, NORES, NODROP)\
	HANDLER(IOIsKeyPressing, ::vl::presentation::VKEY, bool, REQ, RES, NODROP)\
	HANDLER(IOIsKeyToggled, ::vl::presentation::VKEY, bool, REQ, RES, NODROP)\
	HANDLER(WindowGetBounds, void, ::vl::presentation::remoteprotocol::WindowSizingConfig, NOREQ, RES, NODROP)\
	HANDLER(WindowNotifySetTitle, ::vl::WString, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetEnabled, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetTopMost, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetShowInTaskBar, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetCustomFrameMode, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetMaximizedBox, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetMinimizedBox, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetBorder, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetSizeBox, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetIconVisible, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetTitleBar, bool, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetBounds, ::vl::presentation::NativeRect, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifySetClientSize, ::vl::presentation::NativeSize, void, REQ, NORES, DROPREP)\
	HANDLER(WindowNotifyActivate, void, void, NOREQ, NORES, DROPREP)\
	HANDLER(WindowNotifyShow, ::vl::presentation::remoteprotocol::WindowShowing, void, REQ, NORES, DROPREP)\
	HANDLER(RendererCreated, ::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::RendererCreation>>, void, REQ, NORES, NODROP)\
	HANDLER(RendererDestroyed, ::vl::Ptr<::vl::collections::List<::vl::vint>>, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_SolidBorder, ::vl::presentation::remoteprotocol::ElementDesc_SolidBorder, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_SinkBorder, ::vl::presentation::remoteprotocol::ElementDesc_SinkBorder, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_SinkSplitter, ::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_SolidBackground, ::vl::presentation::remoteprotocol::ElementDesc_SolidBackground, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_GradientBackground, ::vl::presentation::remoteprotocol::ElementDesc_GradientBackground, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_InnerShadow, ::vl::presentation::remoteprotocol::ElementDesc_InnerShadow, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_Polygon, ::vl::presentation::remoteprotocol::ElementDesc_Polygon, void, REQ, NORES, NODROP)\
	HANDLER(RendererUpdateElement_SolidLabel, ::vl::presentation::remoteprotocol::ElementDesc_SolidLabel, void, REQ, NORES, NODROP)\
	HANDLER(RendererBeginRendering, void, void, NOREQ, NORES, NODROP)\
	HANDLER(RendererRenderElement, ::vl::presentation::remoteprotocol::ElementRendering, void, REQ, NORES, NODROP)\
	HANDLER(RendererEndRendering, void, ::vl::presentation::remoteprotocol::ElementMeasurings, NOREQ, RES, NODROP)\

#define GACUI_REMOTEPROTOCOL_EVENTS(HANDLER)\
	HANDLER(ControllerConnect, void, NOREQ, NODROP)\
	HANDLER(ControllerDisconnect, void, NOREQ, NODROP)\
	HANDLER(ControllerRequestExit, void, NOREQ, NODROP)\
	HANDLER(ControllerForceExit, void, NOREQ, NODROP)\
	HANDLER(ControllerScreenUpdated, ::vl::presentation::remoteprotocol::ScreenConfig, REQ, DROPREP)\
	HANDLER(IOGlobalShortcutKey, ::vl::vint, REQ, NODROP)\
	HANDLER(IOButtonDown, ::vl::presentation::remoteprotocol::IOMouseInfoWithButton, REQ, NODROP)\
	HANDLER(IOButtonDoubleClick, ::vl::presentation::remoteprotocol::IOMouseInfoWithButton, REQ, NODROP)\
	HANDLER(IOButtonUp, ::vl::presentation::remoteprotocol::IOMouseInfoWithButton, REQ, NODROP)\
	HANDLER(IOHWheel, ::vl::presentation::NativeWindowMouseInfo, REQ, NODROP)\
	HANDLER(IOVWheel, ::vl::presentation::NativeWindowMouseInfo, REQ, NODROP)\
	HANDLER(IOMouseMoving, ::vl::presentation::NativeWindowMouseInfo, REQ, DROPCON)\
	HANDLER(IOMouseEntered, void, NOREQ, NODROP)\
	HANDLER(IOMouseLeaved, void, NOREQ, NODROP)\
	HANDLER(IOKeyDown, ::vl::presentation::NativeWindowKeyInfo, REQ, NODROP)\
	HANDLER(IOKeyUp, ::vl::presentation::NativeWindowKeyInfo, REQ, NODROP)\
	HANDLER(IOChar, ::vl::presentation::NativeWindowCharInfo, REQ, NODROP)\
	HANDLER(WindowBoundsUpdated, ::vl::presentation::remoteprotocol::WindowSizingConfig, REQ, DROPREP)\
	HANDLER(WindowActivatedUpdated, bool, REQ, DROPREP)\

#define GACUI_REMOTEPROTOCOL_MESSAGE_REQUEST_TYPES(HANDLER)\
	HANDLER(::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::GlobalShortcutKey>>)\
	HANDLER(::vl::Ptr<::vl::collections::List<::vl::presentation::remoteprotocol::RendererCreation>>)\
	HANDLER(::vl::Ptr<::vl::collections::List<::vl::vint>>)\
	HANDLER(::vl::WString)\
	HANDLER(::vl::presentation::NativeRect)\
	HANDLER(::vl::presentation::NativeSize)\
	HANDLER(::vl::presentation::VKEY)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_GradientBackground)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_InnerShadow)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_Polygon)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_SinkBorder)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_SinkSplitter)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_SolidBackground)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_SolidBorder)\
	HANDLER(::vl::presentation::remoteprotocol::ElementDesc_SolidLabel)\
	HANDLER(::vl::presentation::remoteprotocol::ElementRendering)\
	HANDLER(::vl::presentation::remoteprotocol::WindowShowing)\
	HANDLER(bool)\

#define GACUI_REMOTEPROTOCOL_MESSAGE_RESPONSE_TYPES(HANDLER)\
	HANDLER(::vl::presentation::remoteprotocol::ElementMeasurings)\
	HANDLER(::vl::presentation::remoteprotocol::FontConfig)\
	HANDLER(::vl::presentation::remoteprotocol::ScreenConfig)\
	HANDLER(::vl::presentation::remoteprotocol::WindowSizingConfig)\
	HANDLER(bool)\

#define GACUI_REMOTEPROTOCOL_EVENT_REQUEST_TYPES(HANDLER)\
	HANDLER(::vl::presentation::NativeWindowCharInfo)\
	HANDLER(::vl::presentation::NativeWindowKeyInfo)\
	HANDLER(::vl::presentation::NativeWindowMouseInfo)\
	HANDLER(::vl::presentation::remoteprotocol::IOMouseInfoWithButton)\
	HANDLER(::vl::presentation::remoteprotocol::ScreenConfig)\
	HANDLER(::vl::presentation::remoteprotocol::WindowSizingConfig)\
	HANDLER(::vl::vint)\
	HANDLER(bool)\

}

#endif
