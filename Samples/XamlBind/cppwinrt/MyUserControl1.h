#pragma once
#include "MyUserControl1.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct MyUserControl1 : MyUserControl1T<MyUserControl1>
    {
        MyUserControl1() = default;

        hstring NonDPProperty();
        void NonDPProperty(hstring const& value);
        winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        std::wstring _nonDP {L"Value not set"};
        event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> _event;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct MyUserControl1 : MyUserControl1T<MyUserControl1, implementation::MyUserControl1>
    {
    };
}
