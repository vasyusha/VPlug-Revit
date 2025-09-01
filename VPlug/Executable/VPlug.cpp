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
	return Result::Succeeded;
}

Result VPlug::Main::OnShutdown(UIControlledApplication^ app) {
	return Result::Succeeded;
}
