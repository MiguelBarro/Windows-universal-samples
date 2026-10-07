#pragma once
#include "SecondaryPage.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct SecondaryPage : SecondaryPageT<SecondaryPage>
    {
        SecondaryPage();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct SecondaryPage : SecondaryPageT<SecondaryPage, implementation::SecondaryPage>
    {
    };
}
