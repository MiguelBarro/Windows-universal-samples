#pragma once
// Both generated headers are necessary in this very order
#include "Scenario1_Basic.g.h"
#include "Scenario1_Basic.xaml.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario1_Basic : Scenario1_BasicT<Scenario1_Basic>
    {
        Scenario1_Basic();

        void ClickToPlaySource_ImageOpened(IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario1_Basic : Scenario1_BasicT<Scenario1_Basic, implementation::Scenario1_Basic>
    {
    };
}
