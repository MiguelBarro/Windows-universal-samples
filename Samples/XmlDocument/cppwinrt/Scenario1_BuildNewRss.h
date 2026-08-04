#pragma once
#include "Scenario1_BuildNewRss.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario1_BuildNewRss : Scenario1_BuildNewRssT<Scenario1_BuildNewRss>
    {
        Scenario1_BuildNewRss();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Scenario1BtnDefault_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::SDKTemplate::MainPage rootPage_ { nullptr };
        winrt::fire_and_forget Scenario1Init();
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario1_BuildNewRss : Scenario1_BuildNewRssT<Scenario1_BuildNewRss, implementation::Scenario1_BuildNewRss>
    {
    };
}
