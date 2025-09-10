[![Revit](https://img.shields.io/badge/Revit-2021+-blue.svg)](https://www.autodesk.com/products/revit/overview)
[![Revit](https://img.shields.io/badge/Revit-API-green.svg)](https://www.revitapidocs.com)
[![.NET](https://img.shields.io/badge/.NET%20Framework-4.8-512BD4.svg)](https://dotnet.microsoft.com/download/dotnet-framework)
[![.NET](https://img.shields.io/badge/.NET-API-red.svg)](https://learn.microsoft.com/en-us/dotnet/api/?view=netframework-4.8.1)
[![C++/CLI](https://img.shields.io/badge/C++/CLI-Bridge--between--C♯--&--C++-lightgrey.svg)](https://en.wikipedia.org/wiki/C++/CLI) 
[![Made With](https://img.shields.io/badge/Made%20with-C++/CLI-ff69b4.svg)](https://docs.microsoft.com/cpp/dotnet/dotnet-programming-with-cpp-cli-visual-cpp)


<h1 align="center">VPlug-Revit</h1>
<h4>In this repository i am developing a plugin for Autodesk Revit</h4>
<h2>Why C++/CLI?</h2>
<h4>This project deliberately uses "C++/CLI" instead of the more common "C#". This makes sense in several scenarios.</h4>
<h4> - :books: Educational Objective: This project serves as a visual aid on how to work with cross-language interoperability in the .NET and Revit ecosystem.</h4>
<h4> - :link: Integration of existing C++ libraries</h4>
<h4> - :rocket: Performance</h4>
<h2>Project goal</h2>
<h4> - :pushpin: Learn to work with C++/CLI</h4>
<h4> - :pushpin: Learn RevitAPI</h4>
<h4> - :pushpin: Create functionality that simplifies the work of BIM specialists and designers</h4>

<h4>The project is being developed in Visual Studio 2022</h4>
<hr></hr>

## Register Plugin

Create file .addin in the directory X:\Users\\%USER%\AppData\Roaming\Autodesk\Revit\Addins\20XX\

```xml
<?xml version="1.0" encoding="utf-8" standalone="no"?>
<RevitAddIns>
  <AddIn Type="Application">
    <Name>VPlug</Name>
    <Assembly>"%your_path%\VPlug.dll"</Assembly>
    <AddInId>{75B71A2F-2ACD-48CE-8518-FF869D3A8440}</AddInId>
    <FullClassName>VPlug.Main</FullClassName>
    <VendorId>vasyusha</VendorId>
    <VendorDescription>https://github.com/vasyusha/VPlug-Revit</VendorDescription>
  </AddIn>
</RevitAddIns>
```



## Project tree
```
VPlug/
├───Configuration/                  # configuration file examples
│   └───Parameter_Checks/           # checking parameters are filled
├───Executable/						# executable files
│   ├───Commands/					# plugin function initialization files
│   ├───Config/						# configuration processing
│   │   └───json/					# processing json
│   ├───Export/						# export processing
│   │   └───html/					# export html
│   ├───Revit/						# wrappers, helper classes, functions for RevitAPI
│   │   ├───Elements/				# Revit element wrappers
│   │   ├───Filters/				# filtering, searching, customization
│   │   └───Services/				# logic of elements and work
│   └───UI/							# visual representation
│       ├───VPControls/				# Controls
│       └───VPForms/				# Forms
└───Headlines/                		# header files
    ├───Commands/					# plugin function initialization files
    ├───Config/						# configuration processing
    │   └───json/					# processing json
    ├───Export/						# export processing
    │   └───html/					# export html
    ├───Revit/						# wrappers, helper classes, functions for RevitAPI
    │   ├───Elements/				# Revit element wrappers
    │   ├───Filters/				# filtering, searching, customization
    │   └───Services/				# logic of elements and work
    └───UI/							# visual representation
        ├───VPControls/				# Controls
        └───VPForms/				# Forms
```
