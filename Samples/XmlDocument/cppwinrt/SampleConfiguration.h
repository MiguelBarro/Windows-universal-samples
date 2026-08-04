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

#pragma once
#include "pch.h"

namespace winrt::SDKTemplate
{
    inline bool check_enumerator(hresult hr)
    {
        check_hresult(hr);
        return hr == S_OK;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Data::Xml::Dom::XmlDocument>
    LoadXmlFile(winrt::hstring folder, winrt::hstring file);

    void RichEditBoxSetText(
            winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
            winrt::hstring msg,
            winrt::Windows::UI::Color color,
            bool fReadOnly);

    void RichEditBoxSetError(
            winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
            winrt::hstring errorMsg);

    void RichEditBoxSetMsg(
            winrt::Windows::UI::Xaml::Controls::RichEditBox richEditBox,
            winrt::hstring msg,
            bool fReadOnly);
}
