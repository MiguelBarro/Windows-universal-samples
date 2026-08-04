#pragma once
#include "Scenario4_GiftDispatch.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario4_GiftDispatch : Scenario4_GiftDispatchT<Scenario4_GiftDispatch>
    {
        Scenario4_GiftDispatch();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Scenario4BtnDefault_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::SDKTemplate::MainPage rootPage_ { nullptr };
        winrt::fire_and_forget Scenario4Init();
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario4_GiftDispatch : Scenario4_GiftDispatchT<Scenario4_GiftDispatch, implementation::Scenario4_GiftDispatch>
    {
    };
}
