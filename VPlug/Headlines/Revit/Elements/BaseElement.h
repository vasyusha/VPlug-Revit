#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Elements {

public ref class BaseElement {
private:
	String^ id_;
	String^ name_;
	String^ guid_;
	String^ category_;

	Dictionary<String^, String^>^ parameters_;
public:
	virtual void SetId(String^ id);
	virtual String^ GetId();

	virtual void SetName(String^ name);
	virtual String^ GetName();

	virtual void SetGuid(String^ guid);
	virtual String^ GetGuid();

	virtual void SetCategoryName(String^ category);
	virtual String^ GetCategoryName();

	virtual void SetParameters(String^ key, String^ value);
	virtual Dictionary<String^, String^>^ GetParameters();
};

}