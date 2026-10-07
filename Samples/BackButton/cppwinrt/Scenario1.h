#pragma once
#include "Scenario1.g.h"

#include "MainPage.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario1 : Scenario1T<Scenario1>
    {
        Scenario1();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Button_Click(IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void CheckBox_Toggle(IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

    private:

        SDKTemplate::MainPage rootPage_;
        bool optedIn_ {false};
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario1 : Scenario1T<Scenario1, implementation::Scenario1>
    {
    };
}
