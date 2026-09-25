// ModulePreamble.h
#pragma once

#include "pch.h" // for sources using /FI sake

import std;

#define WINRT_IMPORT_MODULE

// Import the C++/WinRT namespaces used across this project.
// Every module listed here must be produced by the CppWinRTModuleInclude /
// CppWinRTModuleExclude filters in XamlTransform3DAnimations.vcxproj.
import winrt.Transform3DAnimations;

import winrt.Windows.Foundation;
import winrt.Windows.ApplicationModel;
import winrt.Windows.UI;
import winrt.Windows.UI.Xaml;
import winrt.Windows.UI.Xaml.Interop;
import winrt.Windows.UI.Xaml.Markup;
