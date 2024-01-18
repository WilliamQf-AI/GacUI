/***********************************************************************
This file is generated by: Vczh Parser Generator
From parser definition:Ast
Licensed under https://github.com/vczh-libraries/License
***********************************************************************/

#include "GuiRemoteProtocolAst_Json.h"

namespace vl::presentation::remoteprotocol::json_visitor
{
	void AstVisitor::PrintFields(GuiIqDeclaration* node)
	{
	}
	void AstVisitor::PrintFields(GuiIqProtocol* node)
	{
	}
	void AstVisitor::PrintFields(GuiIqRemoteProtocolDefinition* node)
	{
		BeginField(L"declarations");
		BeginArray();
		for (auto&& listItem : node->declarations)
		{
			BeginArrayItem();
			Print(listItem.Obj());
			EndArrayItem();
		}
		EndArray();
		EndField();
	}
	void AstVisitor::PrintFields(GuiIqType* node)
	{
	}

	void AstVisitor::Visit(GuiIqType* node)
	{
		if (!node)
		{
			WriteNull();
			return;
		}
		BeginObject();
		WriteType(L"Type", node);
		PrintFields(static_cast<GuiIqDeclaration*>(node));
		PrintFields(static_cast<GuiIqType*>(node));
		EndObject();
	}

	void AstVisitor::Visit(GuiIqProtocol* node)
	{
		if (!node)
		{
			WriteNull();
			return;
		}
		BeginObject();
		WriteType(L"Protocol", node);
		PrintFields(static_cast<GuiIqDeclaration*>(node));
		PrintFields(static_cast<GuiIqProtocol*>(node));
		EndObject();
	}

	AstVisitor::AstVisitor(vl::stream::StreamWriter& _writer)
		: vl::glr::JsonVisitorBase(_writer)
	{
	}

	void AstVisitor::Print(GuiIqDeclaration* node)
	{
		if (!node)
		{
			WriteNull();
			return;
		}
		node->Accept(static_cast<GuiIqDeclaration::IVisitor*>(this));
	}

	void AstVisitor::Print(GuiIqRemoteProtocolDefinition* node)
	{
		if (!node)
		{
			WriteNull();
			return;
		}
		BeginObject();
		WriteType(L"RemoteProtocolDefinition", node);
		PrintFields(static_cast<GuiIqRemoteProtocolDefinition*>(node));
		EndObject();
	}

}
