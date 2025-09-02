#include "..\..\..\Headlines\UI\VPControls\VPBaseControl.h"

VPControls::VPBaseControl::VPBaseControl(String^ name, int x, int y, int width, int height) {
	Name = name;
	Location = Drawing::Point(x, y);
	Size = Drawing::Size(width, height);
}

VPControls::VPBaseControl^ VPControls::VPBaseControl::SetText(String^ text) {
	Text = text;
	return this;
}

VPControls::VPBaseControl^ VPControls::VPBaseControl::SetClick(EventHandler^ handler) {
	Click += handler;
	return this;
}

VPControls::VPBaseControl^ VPControls::VPBaseControl::SetResize(EventHandler^ handler) {
	Resize += handler;
	return this;
}


VPControls::VPBaseControl^ VPControls::VPBaseControl::SetAnchor(AnchorStyles anchor) {
	Anchor = anchor;
	return this;
}



