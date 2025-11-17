#pragma once
#include "Commands/AuditParameterCommand.h"
#include "Commands/AuditWallOpeningCommand.h"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;


namespace VPlug {

public ref class Main : Autodesk::Revit::UI::IExternalApplication {
public:
	virtual Result OnStartup(UIControlledApplication^ app);
	virtual Result OnShutdown(UIControlledApplication^ app);
};

}//namespace VPlug
