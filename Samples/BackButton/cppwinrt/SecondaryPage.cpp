#include "pch.h"
#include "SecondaryPage.h"
#include "SecondaryPage.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    SecondaryPage::SecondaryPage()
    {
        InitializeComponent();
    }

    void SecondaryPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        using namespace Windows::UI::Core;

        auto optedIn = unbox_value_or<bool>(e.Parameter(), false);
        auto rootFrame = Windows::UI::Xaml::Window::Current().Content().as<Windows::UI::Xaml::Controls::Frame>();

        if ( rootFrame.CanGoBack() && optedIn)
        {   // If we have pages in our in-app backstack and have opted in to showing back, do so
            SystemNavigationManager::GetForCurrentView().AppViewBackButtonVisibility(AppViewBackButtonVisibility::Visible);
        }
        else
        {   // Remove the UI from the title bar if there are no pages in our in-app back stack
            SystemNavigationManager::GetForCurrentView().AppViewBackButtonVisibility(AppViewBackButtonVisibility::Collapsed);
        }
    }
}
