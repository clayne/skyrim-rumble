#include "FormUtil.h"

auto FormUtil::GetFormFromIdentifier(const std::string& a_identifier) -> RE::TESForm*
{
	std::istringstream ss{ a_identifier };
	std::string plugin, id;

	std::getline(ss, plugin, '|');
	std::getline(ss, id);
	RE::FormID relativeID;
	std::istringstream{ id } >> std::hex >> relativeID;
	const auto dataHandler = RE::TESDataHandler::GetSingleton();
	return dataHandler ? dataHandler->LookupForm(relativeID, plugin) : nullptr;
}

auto FormUtil::GetIdentifierFromForm(const RE::TESForm* a_form) -> std::string
{
	auto editorID = a_form->GetFormEditorID();
	if (editorID && strlen(editorID) > 1) {
		return std::format("{}", editorID);
	}
	if (auto file = a_form->GetFile()) {
		return std::format("{:X}|{}", a_form->GetLocalFormID(), file->GetFilename());
	}
	return std::format("{:X}|Generated", a_form->GetLocalFormID());
}
