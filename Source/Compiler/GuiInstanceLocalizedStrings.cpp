#include "GuiInstanceLocalizedStrings.h"
#include "WorkflowCodegen/GuiInstanceLoader_WorkflowCodegen.h"

namespace vl
{
	namespace presentation
	{
		using namespace collections;
		using namespace glr::xml;
		using namespace workflow;
		using namespace workflow::analyzer;
		using namespace reflection::description;

/***********************************************************************
GuiInstanceLocalizedStringsBase
***********************************************************************/

		WString GuiInstanceLocalizedStringsBase::Strings::GetLocalesName()
		{
			return From(locales).Aggregate(WString(L""), [](const WString& a, const WString& b)
				{
					return a == L"" ? b : a + L";" + b;
				});
		}

/***********************************************************************
GuiInstanceLocalizedStringsBase
***********************************************************************/

		Ptr<GuiInstanceLocalizedStringsBase::Strings> GuiInstanceLocalizedStringsBase::LoadStringsFromXml(Ptr<GuiResourceItem> resource, Ptr<glr::xml::XmlElement> xmlStrings, collections::SortedList<WString>& existingLocales, GuiResourceError::List& errors)
		{
			if (xmlStrings->name.value != L"Strings")
			{
				errors.Add(GuiResourceError({ { resource },xmlStrings->codeRange.start }, L"Precompile: Unknown element \"" + xmlStrings->name.value + L"\", it should be \"Strings\"."));
				return nullptr;
			}

			auto attLocales = XmlGetAttribute(xmlStrings, L"Locales");
			if (!attLocales)
			{
				errors.Add(GuiResourceError({ { resource },xmlStrings->codeRange.start }, L"Precompile: Missing attribute \"Locales\" in \"Strings\"."));
				return nullptr;
			}

			auto lss = Ptr(new GuiInstanceLocalizedStrings::Strings);
			lss->tagPosition = { { resource },xmlStrings->name.codeRange.start };
			SplitBySemicolon(attLocales->value.value, lss->locales);

			for (auto locale : lss->locales)
			{
				if (!existingLocales.Contains(locale))
				{
					existingLocales.Add(locale);
				}
				else
				{
					errors.Add(GuiResourceError({ { resource },attLocales->codeRange.start }, L"Precompile: Locale \"" + locale + L"\" already exists."));
				}
			}

			for (auto xmlString : XmlGetElements(xmlStrings))
			{
				if (xmlString->name.value != L"String")
				{
					errors.Add(GuiResourceError({ { resource },xmlString->codeRange.start }, L"Precompile: Unknown element \"" + xmlString->name.value + L"\", it should be \"String\"."));
					continue;
				}

				auto attName = XmlGetAttribute(xmlString, L"Name");
				auto attText = XmlGetAttribute(xmlString, L"Text");

				if (!attName)
				{
					errors.Add(GuiResourceError({ { resource },xmlString->codeRange.start }, L"Precompile: Missing attribute \"Name\" in \"String\"."));
				}
				if (!attText)
				{
					errors.Add(GuiResourceError({ { resource },xmlString->codeRange.start }, L"Precompile: Missing attribute \"Text\" in \"String\"."));
				}

				if (attName && attText)
				{
					if (lss->items.Keys().Contains(attName->value.value))
					{
						errors.Add(GuiResourceError({ { resource },xmlString->codeRange.start }, L"Precompile: String \"" + attName->value.value + L"\" already exists."));
					}
					else
					{
						auto item = Ptr(new GuiInstanceLocalizedStrings::StringItem);
						item->name = attName->value.value;
						item->text = attText->value.value;
						item->textPosition = { {resource},attText->value.codeRange.start };
						item->textPosition.column += 1;
						lss->items.Add(item->name, item);
					}
				}
			}

			return lss;
		}

		Ptr<glr::xml::XmlElement> GuiInstanceLocalizedStringsBase::SaveStringsToXml(Ptr<Strings> lss)
		{
			auto xmlStrings = Ptr(new XmlElement);
			xmlStrings->name.value = L"Strings";
			{
				auto att = Ptr(new XmlAttribute);
				att->name.value = L"Strings";
				att->value.value = lss->GetLocalesName();
				xmlStrings->attributes.Add(att);
			}

			for (auto lssi : lss->items.Values())
			{
				auto xmlString = Ptr(new XmlElement);
				xmlStrings->subNodes.Add(xmlString);
				{
					auto att = Ptr(new XmlAttribute);
					att->name.value = L"Name";
					att->value.value = lssi->name;
					xmlString->attributes.Add(att);
				}
				{
					auto att = Ptr(new XmlAttribute);
					att->name.value = L"Text";
					att->value.value = lssi->text;
					xmlString->attributes.Add(att);
				}
			}

			return xmlStrings;
		}

		Ptr<GuiInstanceLocalizedStrings::TextDesc> GuiInstanceLocalizedStringsBase::ParseLocalizedText(const WString& text, GuiResourceTextPos pos, GuiResourceError::List& errors)
		{
			const wchar_t* reading = text.Buffer();
			const wchar_t* textPosCounter = reading;
			glr::ParsingTextPos formatPos(0, 0);
			auto textDesc = Ptr(new TextDesc);

			auto addError = [&](const WString& message)
			{
				auto errorPos = pos;
				errorPos.row += formatPos.row;
				errorPos.column = (formatPos.row == 0 ? errorPos.column : 0) + formatPos.column;
				errors.Add({ errorPos,message });
			};

			bool addedParameter = true;
			while (*reading)
			{
				const wchar_t* begin = wcsstr(reading, L"$(");
				if (begin)
				{
					auto text = WString::CopyFrom(reading, vint(begin - reading));
					if (addedParameter)
					{
						textDesc->texts.Add(text);
					}
					else
					{
						textDesc->texts[textDesc->texts.Count() - 1] += text;
					}
				}
				else
				{
					break;
				}

				const wchar_t* end = wcsstr(begin, L")");
				if (!end)
				{
					addError(L"Precompile: Does not find matched close bracket.");
					return nullptr;
				}

				while (textPosCounter++ < begin + 2)
				{
					switch (textPosCounter[-1])
					{
					case '\n':
						formatPos.row++;
						formatPos.column = 0;
						break;
					default:
						formatPos.column++;
						break;
					}
				}

				if (end - begin == 3 && wcsncmp(begin, L"$($)", 4) == 0)
				{
					addedParameter = false;
					textDesc->texts[textDesc->texts.Count() - 1] += L"$";
				}
				else
				{
					addedParameter = true;
					const wchar_t* number = begin + 2;
					const wchar_t* numberEnd = number;
					while (L'0' <= *numberEnd && *numberEnd < L'9')
					{
						numberEnd++;
					}

					if (number == numberEnd)
					{
						addError(L"Precompile: Unexpected character, the correct format is $(index) or $(index:function).");
						return nullptr;
					}

					Ptr<ITypeInfo> type;
					WString function;
					if (*numberEnd == L':')
					{
						if (end - numberEnd > 1)
						{
							function = WString::CopyFrom(numberEnd + 1, (vint)(end - numberEnd - 1));
							if (function == L"ShortDate" || function == L"LongDate" || function == L"YearMonthDate" || function == L"ShortTime" || function == L"LongTime")
							{
								type = TypeInfoRetriver<DateTime>::CreateTypeInfo();
							}
							else if (function.Length() >= 5 && (function.Left(5) == L"Date:" || function.Left(5) == L"Time:"))
							{
								type = TypeInfoRetriver<DateTime>::CreateTypeInfo();
							}
							else if (function == L"Number" || function == L"Currency")
							{
								type = TypeInfoRetriver<WString>::CreateTypeInfo();
							}
							else
							{
								addError(L"Precompile: Unknown formatting function name \"" + function + L"\".");
								return nullptr;
							}
						}
						else
						{
							addError(L"Precompile: Unexpected character, the correct format is $(index) or $(index:function).");
							return nullptr;
						}
					}
					else if (numberEnd != end)
					{
						addError(L"Precompile: Unexpected character, the correct format is $(index) or $(index:function).");
						return nullptr;
					}

					if (!type)
					{
						type = TypeInfoRetriver<WString>::CreateTypeInfo();
					}
					textDesc->parameters.Add({ type,function });
					textDesc->positions.Add(wtoi(WString::CopyFrom(number, (vint)(numberEnd - number))));
				}
				reading = end + 1;
			}

			if (*reading || textDesc->texts.Count() == 0)
			{
				textDesc->texts.Add(reading);
			}

			for (auto [i, index] : indexed(From(textDesc->positions).OrderBySelf()))
			{
				if (i != index)
				{
					errors.Add({ pos,L"Precompile: Missing parameter \"" + itow(index) + L"\"." });
					return nullptr;
				}
			}
			return textDesc;
		}

		void GuiInstanceLocalizedStringsBase::FillStringsToTextDescMap(Ptr<Strings> lss, TextDescMap& textDescs, GuiResourceError::List& errors)
		{
			for (auto lssi : lss->items.Values())
			{
				if (auto textDesc = ParseLocalizedText(lssi->text, lssi->textPosition, errors))
				{
					textDescs.Add({ lss,lssi->name }, textDesc);
				}
			}
		}

		void GuiInstanceLocalizedStringsBase::ValidateAgainstDefaultStrings(Ptr<Strings> defaultStrings, collections::List<Ptr<Strings>>& nonDefaultStrings, TextDescMap& textDescs, GuiResourcePrecompileContext& precompileContext, GuiResourceError::List& errors)
		{
			vint errorCount = errors.Count();
			for (auto lss : nonDefaultStrings)
			{
				auto localesName = lss->GetLocalesName();

				auto missing = From(defaultStrings->items.Keys())
					.Except(lss->items.Keys())
					.Aggregate(WString(L""), [](const WString& a, const WString& b)
					{
						return a == L"" ? b : a + L", " + b;
					});
				
				auto extra = From(lss->items.Keys())
					.Except(defaultStrings->items.Keys())
					.Aggregate(WString(L""), [](const WString& a, const WString& b)
					{
						return a == L"" ? b : a + L", " + b;
					});

				if (missing != L"")
				{
					errors.Add({ lss->tagPosition,L"Precompile: Missing strings for locale \"" + localesName + L"\": " + missing + L"." });
				}

				if (extra != L"")
				{
					errors.Add({ lss->tagPosition,L"Precompile: Unnecessary strings for locale \"" + localesName + L"\": " + extra + L"." });
				}
			}
			if (errors.Count() != errorCount)
			{
				return;
			}

			auto defaultLocalesName = defaultStrings->GetLocalesName();
			for (auto lss : nonDefaultStrings)
			{
				auto localesName = lss->GetLocalesName();

				for (auto lssi : lss->items.Values())
				{
					if (auto textDesc = ParseLocalizedText(lssi->text, lssi->textPosition, errors))
					{
						textDescs.Add({ lss,lssi->name }, textDesc);
						auto defaultDesc = textDescs[{defaultStrings, lssi->name}];
						if (defaultDesc->parameters.Count() != textDesc->parameters.Count())
						{
							errors.Add({ lss->tagPosition,L"String \"" + lssi->name + L"\" in locales \"" + defaultLocalesName + L"\" and \"" + localesName + L"\" have different numbers of parameters." });
						}
						else
						{
							for (vint i = 0; i < textDesc->parameters.Count(); i++)
							{
								auto defaultParameter = defaultDesc->parameters[defaultDesc->positions[i]];
								auto parameter = textDesc->parameters[textDesc->positions[i]];

								if (defaultParameter.key->GetTypeDescriptor()->GetTypeName() != parameter.key->GetTypeDescriptor()->GetTypeName())
								{
									errors.Add({ lss->tagPosition,L"Parameter \"" + itow(i) + L"\" in String \"" + lssi->name + L"\" in locales \"" + defaultLocalesName + L"\" and \"" + localesName + L"\" are in different types \"" + defaultParameter.key->GetTypeFriendlyName() + L"\" and \"" + parameter.key->GetTypeFriendlyName() + L"\"." });
								}
							}
						}
					}
				}
			}
			if (errors.Count() != errorCount)
			{
				return;
			}
		}

		WString GuiInstanceLocalizedStringsBase::GetInterfaceTypeName(const WString& className, bool hasNamespace)
		{
			auto pair = INVLOC.FindLast(className, L"::", Locale::None);
			if (pair.key == -1)
			{
				return L"I" + className + L"Strings";
			}
			else
			{
				auto ns = className.Left(pair.key + 2);
				auto name = className.Right(className.Length() - ns.Length());
				return(hasNamespace ? ns : L"") + L"I" + name + L"Strings";
			}
		}

		WString GuiInstanceLocalizedStringsBase::GenerateStringsCppName(Ptr<Strings> lss)
		{
			auto encoded = From(lss->locales)
				.Aggregate(
					WString::Empty,
					[](auto&& a, auto&& b)
					{
						return a + WString::Unmanaged(L"_") + b;
					});
			return WString::Unmanaged(L"<ls") + encoded + WString::Unmanaged(L">BuildStrings");
		}

		Ptr<workflow::WfFunctionDeclaration> GuiInstanceLocalizedStringsBase::GenerateTextDescFunction(Ptr<TextDesc> textDesc, const WString& functionName, workflow::WfFunctionKind functionKind)
		{
			auto func = Ptr(new WfFunctionDeclaration);
			func->functionKind = functionKind;
			func->anonymity = WfFunctionAnonymity::Named;
			func->name.value = functionName;
			func->returnType = GetTypeFromTypeInfo(TypeInfoRetriver<WString>::CreateTypeInfo().Obj());
			for (vint i = 0; i < textDesc->positions.Count(); i++)
			{
				auto type = textDesc->parameters[textDesc->positions[i]];

				auto argument = Ptr(new WfFunctionArgument);
				argument->name.value = L"<ls>" + itow(i);
				argument->type = GetTypeFromTypeInfo(type.key.Obj());
				func->arguments.Add(argument);
			}

			return func;
		}

		Ptr<workflow::WfExpression> GuiInstanceLocalizedStringsBase::GenerateStringsConstructor(const WString& interfaceName, TextDescMap& textDescs, Ptr<Strings> lss)
		{
			auto lsExpr = Ptr(new WfNewInterfaceExpression);
			{
				auto refType = Ptr(new WfReferenceType);
				refType->name.value = interfaceName;

				auto refPointer = Ptr(new WfSharedPointerType);
				refPointer->element = refType;

				lsExpr->type = refPointer;
			}

			for (auto lssi : lss->items.Values())
			{
				auto textDesc = textDescs[{lss, lssi->name}];
				auto func = GenerateTextDescFunction(textDesc, lssi->name, WfFunctionKind::Override);
				lsExpr->declarations.Add(func);

				auto block = Ptr(new WfBlockStatement);
				func->statement = block;

				Ptr<WfExpression> resultExpr;

				auto appendExpr = [&](Ptr<WfExpression> strExpr)
				{
					if (resultExpr)
					{
						auto binaryExpr = Ptr(new WfBinaryExpression);
						binaryExpr->op = WfBinaryOperator::FlagAnd;
						binaryExpr->first = resultExpr;
						binaryExpr->second = strExpr;

						resultExpr = binaryExpr;
					}
					else
					{
						resultExpr = strExpr;
					}
				};

				for (vint i = 0; i < textDesc->parameters.Count(); i++)
				{
					auto varDesc = Ptr(new WfVariableDeclaration);
					varDesc->name.value = L"<ls>_" + itow(i);

					auto varStat = Ptr(new WfVariableStatement);
					varStat->variable = varDesc;
					block->statements.Add(varStat);

					auto type = textDesc->parameters[i].key;
					auto function = textDesc->parameters[i].value;
					auto index = textDesc->positions[i];

					if (function == L"ShortDate" || function == L"LongDate" || function == L"YearMonthDate" || function == L"ShortTime" || function == L"LongTime")
					{
						auto refLoc = GetExpressionFromTypeDescriptor(description::GetTypeDescriptor<Localization>());

						auto refFormats = Ptr(new WfChildExpression);
						refFormats->parent = refLoc;
						refFormats->name.value = L"Get" + function + L"Formats";

						auto refLocale = Ptr(new WfReferenceExpression);
						refLocale->name.value = L"<ls>locale";

						auto callFormats = Ptr(new WfCallExpression);
						callFormats->function = refFormats;
						callFormats->arguments.Add(refLocale);

						auto refFirst = Ptr(new WfChildExpression);
						refFirst->parent = GetExpressionFromTypeDescriptor(description::GetTypeDescriptor<helper_types::LocalizedStrings>());
						refFirst->name.value = L"FirstOrEmpty";

						auto callFirst = Ptr(new WfCallExpression);
						{
							callFirst->function = refFirst;
							callFirst->arguments.Add(callFormats);
						}

						auto refLocale2 = Ptr(new WfReferenceExpression);
						refLocale2->name.value = L"<ls>locale";

						auto refParameter = Ptr(new WfReferenceExpression);
						refParameter->name.value = L"<ls>" + itow(index);

						auto refLoc2 = GetExpressionFromTypeDescriptor(description::GetTypeDescriptor<Localization>());

						auto refFD = Ptr(new WfChildExpression);
						refFD->parent = refLoc2;
						refFD->name.value = L"Format" + function.Right(4);

						auto callFD = Ptr(new WfCallExpression);
						callFD->function = refFD;
						callFD->arguments.Add(refLocale2);
						callFD->arguments.Add(callFirst);
						callFD->arguments.Add(refParameter);

						varDesc->expression = callFD;
					}
					else if (function.Length() >= 5 && (function.Left(5) == L"Date:" || function.Left(5) == L"Time:"))
					{
						auto refLocale = Ptr(new WfReferenceExpression);
						refLocale->name.value = L"<ls>locale";

						auto refFormat = Ptr(new WfStringExpression);
						refFormat->value.value = function.Right(function.Length() - 5);

						auto refParameter = Ptr(new WfReferenceExpression);
						refParameter->name.value = L"<ls>" + itow(index);

						auto refLoc2 = GetExpressionFromTypeDescriptor(description::GetTypeDescriptor<Localization>());

						auto refFD = Ptr(new WfChildExpression);
						refFD->parent = refLoc2;
						refFD->name.value = L"Format" + function.Left(4);

						auto callFD = Ptr(new WfCallExpression);
						callFD->function = refFD;
						callFD->arguments.Add(refLocale);
						callFD->arguments.Add(refFormat);
						callFD->arguments.Add(refParameter);

						varDesc->expression = callFD;
					}
					else if (function == L"Number" || function == L"Currency")
					{
						auto refLocale = Ptr(new WfReferenceExpression);
						refLocale->name.value = L"<ls>locale";

						auto refParameter = Ptr(new WfReferenceExpression);
						refParameter->name.value = L"<ls>" + itow(index);

						auto refLoc2 = GetExpressionFromTypeDescriptor(description::GetTypeDescriptor<Localization>());

						auto refFD = Ptr(new WfChildExpression);
						refFD->parent = refLoc2;
						refFD->name.value = L"Format" + function;

						auto callFD = Ptr(new WfCallExpression);
						callFD->function = refFD;
						callFD->arguments.Add(refLocale);
						callFD->arguments.Add(refParameter);

						varDesc->expression = callFD;
					}
					else
					{
						auto refParameter = Ptr(new WfReferenceExpression);
						refParameter->name.value = L"<ls>" + itow(index);

						varDesc->expression = refParameter;
					}
				}

				for (vint i = 0; i < textDesc->texts.Count(); i++)
				{
					if (textDesc->texts[i] != L"")
					{
						auto strExpr = Ptr(new WfStringExpression);
						strExpr->value.value = textDesc->texts[i];
						appendExpr(strExpr);
					}

					if (i < textDesc->parameters.Count())
					{
						auto refExpr = Ptr(new WfReferenceExpression);
						refExpr->name.value = L"<ls>_" + itow(i);
						appendExpr(refExpr);
					}
				}

				if (!resultExpr)
				{
					resultExpr = Ptr(new WfStringExpression);
				}

				auto returnStat = Ptr(new WfReturnStatement);
				returnStat->expression = resultExpr;

				block->statements.Add(returnStat);
			}

			return lsExpr;
		}

		Ptr<workflow::WfFunctionDeclaration> GuiInstanceLocalizedStringsBase::GenerateBuildStringsFunction(const WString& interfaceName, TextDescMap& textDescs, Ptr<Strings> lss)
		{
			auto func = Ptr(new WfFunctionDeclaration);
			func->functionKind = WfFunctionKind::Static;
			func->anonymity = WfFunctionAnonymity::Named;
			func->name.value = GenerateStringsCppName(lss);
			{
				auto refType = Ptr(new WfReferenceType);
				refType->name.value = interfaceName;

				auto refPointer = Ptr(new WfSharedPointerType);
				refPointer->element = refType;

				func->returnType = refPointer;
			}
			{
				auto argument = Ptr(new WfFunctionArgument);
				argument->name.value = L"<ls>locale";
				argument->type = GetTypeFromTypeInfo(TypeInfoRetriver<Locale>::CreateTypeInfo().Obj());
				func->arguments.Add(argument);
			}

			auto block = Ptr(new WfBlockStatement);
			func->statement = block;
			
			auto returnStat = Ptr(new WfReturnStatement);
			returnStat->expression = GenerateStringsConstructor(interfaceName, textDescs, lss);
			block->statements.Add(returnStat);

			return func;
		}

/***********************************************************************
GuiInstanceLocalizedStrings
***********************************************************************/

		Ptr<GuiInstanceLocalizedStrings> GuiInstanceLocalizedStrings::LoadFromXml(Ptr<GuiResourceItem> resource, Ptr<glr::xml::XmlDocument> xml, GuiResourceError::List& errors)
		{
			auto ls = Ptr(new GuiInstanceLocalizedStrings);

			if (xml->rootElement->name.value!=L"LocalizedStrings")
			{
				errors.Add(GuiResourceError({ { resource },xml->rootElement->codeRange.start }, L"Precompile: The root element of localized strings should be \"LocalizedStrings\"."));
				return nullptr;
			}
			ls->tagPosition = { {resource},xml->rootElement->name.codeRange.start };

			auto attClassName = XmlGetAttribute(xml->rootElement, L"ref.Class");
			if (!attClassName)
			{
				errors.Add(GuiResourceError({ { resource },xml->rootElement->codeRange.start }, L"Precompile: Missing attribute \"ref.Class\" in \"LocalizedStrings\"."));
			}
			else
			{
				ls->className = attClassName->value.value;
			}

			auto attDefaultLocale = XmlGetAttribute(xml->rootElement, L"DefaultLocale");
			if (!attDefaultLocale)
			{
				errors.Add(GuiResourceError({ { resource },xml->rootElement->codeRange.start }, L"Precompile: Missing attribute \"DefaultLocale\" in \"LocalizedStrings\"."));
			}
			else
			{
				ls->defaultLocale = attDefaultLocale->value.value;
			}

			if (!attClassName || !attDefaultLocale)
			{
				return nullptr;
			}

			SortedList<WString> existingLocales;
			for (auto xmlStrings : XmlGetElements(xml->rootElement))
			{
				if (auto lss = LoadStringsFromXml(resource, xmlStrings, existingLocales, errors))
				{
					ls->strings.Add(lss);
					if (lss->locales.Contains(ls->defaultLocale))
					{
						ls->defaultStrings = lss;
					}
				}
			}

			if (!ls->defaultStrings)
			{
				errors.Add(GuiResourceError({ { resource },xml->rootElement->codeRange.start }, L"Precompile: Strings for the default locale \"" + ls->defaultLocale + L"\" is not defined."));
			}

			return ls;
		}

		Ptr<glr::xml::XmlElement> GuiInstanceLocalizedStrings::SaveToXml()
		{
			auto xml = Ptr(new XmlElement);
			xml->name.value = L"LocalizedStrings";
			{
				auto att = Ptr(new XmlAttribute);
				att->name.value = L"ref.Class";
				att->value.value = className;
				xml->attributes.Add(att);
			}
			{
				auto att = Ptr(new XmlAttribute);
				att->name.value = L"DefaultLocale";
				att->value.value = defaultLocale;
				xml->attributes.Add(att);
			}

			for (auto lss : strings)
			{
				xml->subNodes.Add(SaveStringsToXml(lss));
			}

			return xml;
		}

		Ptr<workflow::WfFunctionDeclaration> GuiInstanceLocalizedStrings::GenerateInstallFunction(const WString& cacheName)
		{
			auto func = Ptr(new WfFunctionDeclaration);
			func->functionKind = WfFunctionKind::Static;
			func->anonymity = WfFunctionAnonymity::Named;
			func->name.value = L"Install";
			{
				auto refVoid = Ptr(new WfPredefinedType);
				refVoid->name = WfPredefinedTypeName::Void;
				func->returnType = refVoid;
			}
			{
				auto argument = Ptr(new WfFunctionArgument);
				argument->name.value = L"<ls>locale";
				argument->type = GetTypeFromTypeInfo(TypeInfoRetriver<Locale>::CreateTypeInfo().Obj());
				func->arguments.Add(argument);
			}
			{
				auto refType = Ptr(new WfReferenceType);
				refType->name.value = GetInterfaceTypeName(className, false);

				auto refPointer = Ptr(new WfSharedPointerType);
				refPointer->element = refType;

				auto argument = Ptr(new WfFunctionArgument);
				argument->name.value = L"<ls>impl";
				argument->type = refPointer;
				func->arguments.Add(argument);
			}

			auto block = Ptr(new WfBlockStatement);
			func->statement = block;

			{
				auto ifStat = Ptr(new WfIfStatement);
				{
					auto refCache = Ptr(new WfReferenceExpression);
					refCache->name.value = cacheName;

					auto refKeys = Ptr(new WfMemberExpression);
					refKeys->parent = refCache;
					refKeys->name.value = L"Keys";

					auto refContains = Ptr(new WfMemberExpression);
					refContains->parent = refKeys;
					refContains->name.value = L"Contains";

					auto refLocale = Ptr(new WfReferenceExpression);
					refLocale->name.value = L"<ls>locale";

					auto callExpr = Ptr(new WfCallExpression);
					callExpr->function = refContains;
					callExpr->arguments.Add(refLocale);

					ifStat->expression = callExpr;
				}

				auto trueBlock = Ptr(new WfBlockStatement);
				ifStat->trueBranch = trueBlock;

				auto raiseStat = Ptr(new WfRaiseExceptionStatement);
				trueBlock->statements.Add(raiseStat);
				{
					auto errorHead = Ptr(new WfStringExpression);
					errorHead->value.value = L"Localized strings \"" + className + L"\" has already registered for locale \"";

					auto refLocale = Ptr(new WfReferenceExpression);
					refLocale->name.value = L"<ls>locale";

					auto errorTail = Ptr(new WfStringExpression);
					errorTail->value.value = L"\".";

					auto concat0 = Ptr(new WfBinaryExpression);
					concat0->op = WfBinaryOperator::FlagAnd;
					concat0->first = errorHead;
					concat0->second = refLocale;

					auto concat1 = Ptr(new WfBinaryExpression);
					concat1->op = WfBinaryOperator::FlagAnd;
					concat1->first = concat0;
					concat1->second = errorTail;

					raiseStat->expression = concat1;
				}

				block->statements.Add(ifStat);
			}
			{
				auto callExpr = Ptr(new WfCallExpression);
				{
					auto refCache = Ptr(new WfReferenceExpression);
					refCache->name.value = cacheName;

					auto refSet = Ptr(new WfMemberExpression);
					refSet->parent = refCache;
					refSet->name.value = L"Set";

					callExpr->function = refSet;
				}
				{
					auto refLocale = Ptr(new WfReferenceExpression);
					refLocale->name.value = L"<ls>locale";

					callExpr->arguments.Add(refLocale);
				}
				{
					auto refImpl = Ptr(new WfReferenceExpression);
					refImpl->name.value = L"<ls>impl";

					callExpr->arguments.Add(refImpl);
				}

				auto exprStat = Ptr(new WfExpressionStatement);
				exprStat->expression = callExpr;
				block->statements.Add(exprStat);
			}

			return func;
		}

		Ptr<workflow::WfFunctionDeclaration> GuiInstanceLocalizedStrings::GenerateGetFunction(const WString& cacheName)
		{
			auto func = Ptr(new WfFunctionDeclaration);
			func->functionKind = WfFunctionKind::Static;
			func->anonymity = WfFunctionAnonymity::Named;
			func->name.value = L"Get";
			{
				auto refType = Ptr(new WfReferenceType);
				refType->name.value = GetInterfaceTypeName(className, false);

				auto refPointer = Ptr(new WfSharedPointerType);
				refPointer->element = refType;

				func->returnType = refPointer;
			}
			{
				auto argument = Ptr(new WfFunctionArgument);
				argument->name.value = L"<ls>locale";
				argument->type = GetTypeFromTypeInfo(TypeInfoRetriver<Locale>::CreateTypeInfo().Obj());
				func->arguments.Add(argument);
			}

			auto block = Ptr(new WfBlockStatement);
			func->statement = block;

			{
				auto ifStat = Ptr(new WfIfStatement);
				{
					auto refCache = Ptr(new WfReferenceExpression);
					refCache->name.value = cacheName;

					auto refKeys = Ptr(new WfMemberExpression);
					refKeys->parent = refCache;
					refKeys->name.value = L"Keys";

					auto refContains = Ptr(new WfMemberExpression);
					refContains->parent = refKeys;
					refContains->name.value = L"Contains";

					auto refLocale = Ptr(new WfReferenceExpression);
					refLocale->name.value = L"<ls>locale";

					auto callExpr = Ptr(new WfCallExpression);
					callExpr->function = refContains;
					callExpr->arguments.Add(refLocale);

					ifStat->expression = callExpr;
				}

				auto trueBlock = Ptr(new WfBlockStatement);
				ifStat->trueBranch = trueBlock;

				{
					auto refCache = Ptr(new WfReferenceExpression);
					refCache->name.value = cacheName;

					auto refLocale = Ptr(new WfReferenceExpression);
					refLocale->name.value = L"<ls>locale";

					auto refGet = Ptr(new WfBinaryExpression);
					refGet->op = WfBinaryOperator::Index;
					refGet->first = refCache;
					refGet->second = refLocale;

					auto returnStat = Ptr(new WfReturnStatement);
					returnStat->expression = refGet;
					trueBlock->statements.Add(returnStat);
				}

				block->statements.Add(ifStat);
			}
			{
				auto refCache = Ptr(new WfReferenceExpression);
				refCache->name.value = cacheName;

				auto strExpr = Ptr(new WfStringExpression);
				strExpr->value.value = defaultLocale;

				auto castExpr = Ptr(new WfExpectedTypeCastExpression);
				castExpr->strategy = WfTypeCastingStrategy::Strong;
				castExpr->expression = strExpr;

				auto refGet = Ptr(new WfBinaryExpression);
				refGet->op = WfBinaryOperator::Index;
				refGet->first = refCache;
				refGet->second = castExpr;

				auto returnStat = Ptr(new WfReturnStatement);
				returnStat->expression = refGet;
				block->statements.Add(returnStat);
			}

			return func;
		}

		Ptr<workflow::WfModule> GuiInstanceLocalizedStrings::Compile(GuiResourcePrecompileContext& precompileContext, const WString& moduleName, GuiResourceError::List& errors)
		{
			vint errorCount = errors.Count();
			TextDescMap textDescs;
			{
				List<Ptr<Strings>> nonDefaultStrings;
				CopyFrom(
					nonDefaultStrings,
					From(strings).Where([this](auto&& lss) { return lss != defaultStrings; })
					);

				FillStringsToTextDescMap(defaultStrings, textDescs, errors);
				ValidateAgainstDefaultStrings(defaultStrings, nonDefaultStrings, textDescs, precompileContext, errors);
			}
			if (errors.Count() != errorCount)
			{
				return nullptr;
			}

			WString cacheName;

			auto module = Ptr(new WfModule);
			module->moduleType = WfModuleType::Module;
			module->name.value = moduleName;

			// interface
			{
				auto lsInterface = Workflow_InstallClass(GetInterfaceTypeName(className, true), module);
				lsInterface->kind = WfClassKind::Interface;
				lsInterface->constructorType = WfConstructorType::SharedPtr;

				for (auto functionName : defaultStrings->items.Keys())
				{
					auto func = GenerateTextDescFunction(textDescs[{defaultStrings, functionName}], functionName, WfFunctionKind::Normal);
					lsInterface->declarations.Add(func);
				}
			}

			// cache
			{
				auto refType = Ptr(new WfReferenceType);
				refType->name.value = GetInterfaceTypeName(className, false);
				
				auto ptrType = Ptr(new WfSharedPointerType);
				ptrType->element = refType;
				
				auto mapType = Ptr(new WfMapType);
				mapType->writability = WfMapWritability::Writable;
				mapType->key = GetTypeFromTypeInfo(TypeInfoRetriver<Locale>::CreateTypeInfo().Obj());
				mapType->value = ptrType;
				
				auto lsCache = Ptr(new WfVariableDeclaration);
				lsCache->type = mapType;
				lsCache->expression = Ptr(new WfConstructorExpression);
				
				cacheName = L"<ls>" + Workflow_InstallWithClass(className, module, lsCache);
				lsCache->name.value = cacheName;
			}

			// class
			{
				auto lsClass = Workflow_InstallClass(className, module);
				for (auto ls : strings)
				{
					lsClass->declarations.Add(GenerateBuildStringsFunction(GetInterfaceTypeName(className, false), textDescs, ls));
				}
				lsClass->declarations.Add(GenerateInstallFunction(cacheName));
				lsClass->declarations.Add(GenerateGetFunction(cacheName));
			}

			// init
			{
				auto lsInit = Ptr(new WfStaticInitDeclaration);
				auto classNameWithoutNs = Workflow_InstallWithClass(className, module, lsInit);

				auto block = Ptr(new WfBlockStatement);
				lsInit->statement = block;

				for (auto ls : strings)
				{
					auto cppName = GenerateStringsCppName(ls);
					for (auto locale : ls->locales)
					{
						Ptr<WfExpression> exprStrings, exprInstall;
						{
							auto refClass = Ptr(new WfReferenceExpression);
							refClass->name.value = classNameWithoutNs;

							auto refStrings = Ptr(new WfChildExpression);
							refStrings->parent = refClass;
							refStrings->name.value = GenerateStringsCppName(ls);

							auto strExpr = Ptr(new WfStringExpression);
							strExpr->value.value = locale;

							auto castExpr = Ptr(new WfExpectedTypeCastExpression);
							castExpr->strategy = WfTypeCastingStrategy::Strong;
							castExpr->expression = strExpr;

							auto callStringsExpr = Ptr(new WfCallExpression);
							callStringsExpr->function = refStrings;
							callStringsExpr->arguments.Add(castExpr);

							exprStrings = callStringsExpr;
						}
						{
							auto strExpr = Ptr(new WfStringExpression);
							strExpr->value.value = locale;

							auto castExpr = Ptr(new WfExpectedTypeCastExpression);
							castExpr->strategy = WfTypeCastingStrategy::Strong;
							castExpr->expression = strExpr;

							auto refClass = Ptr(new WfReferenceExpression);
							refClass->name.value = classNameWithoutNs;

							auto refInstall = Ptr(new WfChildExpression);
							refInstall->parent = refClass;
							refInstall->name.value = L"Install";

							auto callInstallExpr = Ptr(new WfCallExpression);
							callInstallExpr->function = refInstall;
							callInstallExpr->arguments.Add(castExpr);
							callInstallExpr->arguments.Add(exprStrings);

							exprInstall = callInstallExpr;
						}
						auto exprStat = Ptr(new WfExpressionStatement);
						exprStat->expression = exprInstall;
						block->statements.Add(exprStat);
					}
				}
			}

			glr::ParsingTextPos pos(tagPosition.row, tagPosition.column);
			SetCodeRange(module, { pos,pos });
			return module;
		}

/***********************************************************************
GuiInstanceLocalizedStringsInjection
***********************************************************************/

		Ptr<GuiInstanceLocalizedStringsInjection> GuiInstanceLocalizedStringsInjection::LoadFromXml(Ptr<GuiResourceItem> resource, Ptr<glr::xml::XmlDocument> xml, GuiResourceError::List& errors)
		{
			CHECK_FAIL(L"Not Implemented!");
		}

		Ptr<glr::xml::XmlElement> GuiInstanceLocalizedStringsInjection::SaveToXml()
		{
			CHECK_FAIL(L"Not Implemented!");
		}

		Ptr<workflow::WfModule> GuiInstanceLocalizedStringsInjection::Compile(GuiResourcePrecompileContext& precompileContext, const WString& moduleName, GuiResourceError::List& errors)
		{
			CHECK_FAIL(L"Not Implemented!");
		}
	}
}