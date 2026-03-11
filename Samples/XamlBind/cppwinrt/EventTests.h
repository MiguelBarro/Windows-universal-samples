#pragma once
#include "EventTests.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct EventTests : EventTestsT<EventTests>
    {
        EventTests() = default;

        winrt::xBindSampleModel::DataModel Model();
        void Click_RegularArgs(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Click_NoArgs();
        void Click_BaseArgs(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::IInspectable const& e);

    private:
        winrt::xBindSampleModel::DataModel _model;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct EventTests : EventTestsT<EventTests, implementation::EventTests>
    {
    };
}
