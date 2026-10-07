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
    return L"SystemBack C++/WinRT Sample";
}

IVector<Scenario> implementation::MainPage::scenariosInner = winrt::single_threaded_observable_vector<Scenario>(
{
    Scenario{ L"Scenario1", xaml_typename<SDKTemplate::Scenario1>() },
    Scenario{ L"SecondaryPage", xaml_typename<SDKTemplate::SecondaryPage>() },
});

namespace winrt::SDKTemplate::implementation
{
    bool App_OverrideOnLaunched(winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&)
    {
        // Register a global back event handler. This can be registered on a per-page-bases if you only have a subset of your pages
        // that needs to handle back or if you want to do page-specific logic before deciding to navigate back on those pages.
        Windows::UI::Core::SystemNavigationManager::GetForCurrentView().BackRequested(
            [](winrt::Windows::Foundation::IInspectable const&,
               winrt::Windows::UI::Core::BackRequestedEventArgs const& e)
            {
                // retrieve the one and only
                auto app = Windows::UI::Xaml::Application::Current().try_as<SDKTemplate::implementation::App>();

                if (!app)
                    throw hresult_error(E_FAIL, hstring(L"Failed to access App"));

                // assure that root frame is available
                auto rootFrame = app->CreateRootFrame();
                if (rootFrame && rootFrame.CanGoBack() && !e.Handled())
                {
                    e.Handled(true);
                    rootFrame.GoBack();
                }
            });

        // keep the usual shared initialization logic
        return false;
    }
}
