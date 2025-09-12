#pragma once
#include "..\Headlines\VPlug.h"

using namespace System::Windows::Media::Imaging;
Result VPlug::Main::OnStartup(UIControlledApplication^ app) {
	TaskDialog::Show("VPlug", "Plugin loaded successfully");

	String^ tab_name = "VPlug";

	try {
		app->CreateRibbonTab(tab_name);
	} catch (...) {
		TaskDialog::Show("Error", "The plugin already exists");
	}
	
	String^ path = Assembly::GetExecutingAssembly()->Location;

	RibbonPanel^ panel_check_something = app->CreateRibbonPanel(tab_name, "Проверка");

	PulldownButtonData^ pull_button_data_check_something = gcnew PulldownButtonData(
		"check_something",
		"Проверить"
	);

	PulldownButton^ pull_button_check_something = safe_cast<PulldownButton^>(panel_check_something->AddItem(pull_button_data_check_something));

	PushButtonData^ push_button_data_check_filling_param = gcnew PushButtonData(
		"check_filling_param",
		"Заполнение параметров",
		path,
		"Commands.AuditParameterCommand"
	);

	pull_button_check_something->AddPushButton(push_button_data_check_filling_param);

	return Result::Succeeded;
}

Result VPlug::Main::OnShutdown(UIControlledApplication^ app) {
	return Result::Succeeded;
}
