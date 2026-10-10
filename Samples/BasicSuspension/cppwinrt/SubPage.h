#pragma once
#include "SubPage.g.h"

#include <cstdint>

namespace winrt::SDKTemplate::implementation
{
    struct SubPage : SubPageT<SubPage>
    {
        SubPage();

        void Page_Tapped(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e);

        void Navigation_BackRequested(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Core::BackRequestedEventArgs const& e);

        void OnNavigatedFrom(
                winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void OnNavigatedTo(
                winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

    private:
        SDKTemplate::Item _item {nullptr};
        Windows::UI::Core::SystemNavigationManager::BackRequested_revoker _auto_revokeBR;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct SubPage : SubPageT<SubPage, implementation::SubPage>
    {
    };
}
