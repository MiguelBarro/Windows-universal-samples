#pragma once
#include "Scenario5_XSLTTransform.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario5_XSLTTransform : Scenario5_XSLTTransformT<Scenario5_XSLTTransform>
    {
        Scenario5_XSLTTransform();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Scenario5BtnTransformToString_Click(
                winrt::Windows::Foundation::IInspectable sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs e);

        winrt::fire_and_forget Scenario5BtnTransformToDocument_Click(
                winrt::Windows::Foundation::IInspectable sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs e);

    private:
        winrt::SDKTemplate::MainPage rootPage_ { nullptr };
        winrt::fire_and_forget Scenario5Init();
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario5_XSLTTransform : Scenario5_XSLTTransformT<Scenario5_XSLTTransform, implementation::Scenario5_XSLTTransform>
    {
    };
}
