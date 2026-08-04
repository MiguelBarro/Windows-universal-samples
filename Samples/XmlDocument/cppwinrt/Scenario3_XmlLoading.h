#pragma once
#include "Scenario3_XmlLoading.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario3_XmlLoading : Scenario3_XmlLoadingT<Scenario3_XmlLoading>
    {
        Scenario3_XmlLoading();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        winrt::fire_and_forget LaunchUri(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        winrt::fire_and_forget Scenario3BtnBuffer_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        winrt::fire_and_forget Scenario3BtnFile_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::SDKTemplate::MainPage rootPage_ { nullptr };
        winrt::fire_and_forget Scenario3Init();
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario3_XmlLoading : Scenario3_XmlLoadingT<Scenario3_XmlLoading, implementation::Scenario3_XmlLoading>
    {
    };
}
