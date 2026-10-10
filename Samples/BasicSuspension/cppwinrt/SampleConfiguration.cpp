//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "pch.h"
#include <winrt/SDKTemplate.h>
#include "App.h"
#include "MainPage.h"
#include "SampleConfiguration.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace SDKTemplate;

hstring implementation::MainPage::FEATURE_NAME()
{
    return L"BasicSuspension C++/WinRT Sample";
}

IVector<Scenario> implementation::MainPage::scenariosInner = winrt::single_threaded_observable_vector<Scenario>(
{
    Scenario{ L"SubPage", xaml_typename<SDKTemplate::SubPage>() },
});

namespace winrt::SDKTemplate::implementation
{
    constexpr std::wstring sessionStateFilename = L"sessionState.xml";

    void App_LaunchCompleted( winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e) try
    {
        // If this is not the first time the app is run, then restore from the previous session.
        if (e.PreviousExecutionState() != Windows::ApplicationModel::Activation::ApplicationExecutionState::Terminated)
            return;

        Windows::Storage::StorageFile file;
        file = co_await Windows::Storage::ApplicationData::Current().LocalFolder().GetFileAsync(sessionStateFilename);

        // TODO: Load state from previously terminated application
    }
    catch (...) {}
}
