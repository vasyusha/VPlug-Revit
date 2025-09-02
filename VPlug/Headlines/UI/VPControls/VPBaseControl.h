#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace  VPControls {

public ref class VPBaseControl : public Control {
public:
	VPBaseControl(String^ name, int x, int y, int width, int height);

	VPBaseControl^ SetText(String^ text);

	VPBaseControl^ SetClick(EventHandler^ handler);
	
	VPBaseControl^ SetResize(EventHandler^ handler);

	VPBaseControl^ SetAnchor(AnchorStyles anchor);
};
	
}
