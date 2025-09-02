#pragma once
#include "VPBaseControl.h"

using namespace System;
using namespace System::Windows::Forms;

namespace VPControls {

public ref class VPButton : public VPBaseControl {
public:
	VPButton(String^ name, int x, int y, int width, int height);
};

}
