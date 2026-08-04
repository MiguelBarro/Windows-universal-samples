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
#include "MainPage.h"
#include "SampleConfiguration.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace SDKTemplate;

hstring implementation::MainPage::FEATURE_NAME()
{
    return L"XmlDocument C++/WinRT Sample";
}

IVector<Scenario> implementation::MainPage::scenariosInner = winrt::single_threaded_observable_vector<Scenario>(
{
    Scenario{L"Build New RSS", xaml_typename<SDKTemplate::Scenario1_BuildNewRss>()},
    Scenario{L"DOM Load/Save", xaml_typename<SDKTemplate::Scenario2_MarkHotProducts>()},
    Scenario{L"Set Load Settings", xaml_typename<SDKTemplate::Scenario3_XmlLoading>()},
    Scenario{L"XPath Query", xaml_typename<SDKTemplate::Scenario4_GiftDispatch>()},
    Scenario{L"XSLT Transformation", xaml_typename<SDKTemplate::Scenario5_XSLTTransform>()}
});

winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Data::Xml::Dom::XmlDocument>
winrt::SDKTemplate::LoadXmlFile(winrt::hstring folder, winrt::hstring file)
{
    auto storageFolder =
        co_await Windows::ApplicationModel::Package::Current().InstalledLocation().GetFolderAsync(folder);
    auto storageFile = co_await storageFolder.GetFileAsync(file);

    winrt::Windows::Data::Xml::Dom::XmlLoadSettings loadSettings;
    loadSettings.ProhibitDtd(false);
    loadSettings.ResolveExternals(false);
    auto doc =
        co_await winrt::Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(storageFile, loadSettings);
    co_return doc;
}

void winrt::SDKTemplate::RichEditBoxSetText(
        winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
        winrt::hstring msg,
        winrt::Windows::UI::Color color,
        bool fReadOnly)
{
    richEditBox.IsReadOnly(false);
    richEditBox.Document().SetText(Windows::UI::Text::TextSetOptions::None, msg);
    richEditBox.Foreground(winrt::Windows::UI::Xaml::Media::SolidColorBrush(color));
    richEditBox.IsReadOnly(fReadOnly);
}

void winrt::SDKTemplate::RichEditBoxSetError(
        winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
        winrt::hstring errorMsg)
{
    RichEditBoxSetText(richEditBox, errorMsg, winrt::Windows::UI::Colors::Red(), true);
}

void winrt::SDKTemplate::RichEditBoxSetMsg(
        winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
        winrt::hstring msg,
        bool fReadOnly)
{
    RichEditBoxSetText(richEditBox, msg, winrt::Windows::UI::Colors::White(), fReadOnly);
}
