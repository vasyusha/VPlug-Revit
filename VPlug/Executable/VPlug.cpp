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

	RibbonPanel^ panel_bim_helper = app->CreateRibbonPanel(tab_name, "Бим помошник");
	
	PushButtonData^ button_bim_helper_check_param = gcnew PushButtonData(
		"_bim_helper_check_param_",
		"Пров. заполн. парам.",
		path,
		"Commands.AuditParameterCommand"
	);
	PushButton^ push_bim_helper_check_param = dynamic_cast<PushButton^>(panel_bim_helper->AddItem(button_bim_helper_check_param));

	return Result::Succeeded;
}

Result VPlug::Main::OnShutdown(UIControlledApplication^ app) {
	return Result::Succeeded;
}
