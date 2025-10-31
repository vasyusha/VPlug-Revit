#pragma once

#include "../../Headers/UI/MyForms/FormAuditParameter.h"
#include "../../Headers/Config/json/JsonReaderAuditParameter.h"
#include "../../Headers/Revit/Services/BaseService.h"
#include "../../Headers/Export/html/AuditParameterExportHtml.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Commands {

public ref class AuditScopeSummary {
private:
	String^ scope_;
	bool pass_;
	int totalElement_;
	int passElement_;
	int failedElement_;
	int totalParam_;
	int passedParam_;
	int missedValue_;
	int noParam_;

public:
	property String^ Scope {
		String^ get();
		void set(String^ value);
	};

	property bool Pass {
		bool get();
		void set(bool value);
	};

	property int TotalElement {
		int get();
		void set(int value);
	};

	property int PassedElement {
		int get();
		void set(int value);
	};

	property int FailedElement {
		int get();	
		void set(int value);
	};

	property int TotalParam {
		int get();	
		void set(int value);
	};

	property int PassedParam {
		int get();
		void set(int value);
	};

	property int MissedValue {
		int get();
		void set(int value);
	};

	property int NoParam {
		int get();	
		void set(int value);
	};
};

public ref class AuditResults {
private:
	bool pass_ = true;
	int specPass_;
	int specTotal_;
	int reqPass_;
	int reqTotal_;
	int checkPass_;
	int checkTotal_;

public:
	AuditResults();

	property bool Pass {
		bool get();
		void set(bool value);
	};

	property int SpecPass {
		int get();
		void set(int value);
	};

	property int SpecTotal {
		int get();
		void set(int value);
	};

	property int ReqPass {
		int get();
		void set(int value);
	};

	property int ReqTotal {
		int get();
		void set(int value);
	};

	property int CheckPass {
		int get();
		void set(int value);
	};

	property int CheckTotal {
		int get();
		void set(int value);
	};

	List<AuditScopeSummary^>^ auditScopeSummary;
};

[Transaction(TransactionMode::Manual)]
public ref class AuditParameterCommand : public IExternalCommand {
private:
	Document^ doc_;
	MyForm::FormAuditParameter^ form_;

	String^ method_;
	String^ configPath_;
	String^ exportPath_;

	void SubscriptionEvent();

	void SetAvailableMethods();
	void GetMethod(String^ method);
	
	void GetConfigPath(String^ path);

	void StartPrepare();
	void PrepareCategory();
	void PrepareUserFilterSpec();

	void GetOnChecks(List<String^>^ selected);

	void Audit();
	void AuditCategory();
	void AuditUserFilter();

	AuditScopeSummary^ CreateDataScope(String^ scope, IList<Elements::BaseElement^>^ elements);

	void CompileAuditResult(AuditScopeSummary^ ass);

	void FillTable();

	void Export(String^ path);
	void ExportPrepareCategory(ExportHtml::ReportModel^ repM);

	List<String^>^ checks_;
	List<String^>^ checksSelected_;

	Dictionary<String^, JsonReader::CategorySpec^>^ categorySpecs_;
	Dictionary<String^, JsonReader::UserFilterSpec^>^ userFilterSpecs_;
	Dictionary<String^, List<String^>^>^ groupCheckParameters_;

	Dictionary<String^, List<Elements::BaseElement^>^>^ elements_;

	Dictionary<String^, AuditScopeSummary^>^ dataScopes_;
	
	AuditResults^ res_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}// namespace Command
