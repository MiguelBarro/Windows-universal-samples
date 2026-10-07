#include "pch.h"
#include "Scenario1.h"
#include "Scenario1.g.cpp"

#include "SecondaryPage.h"

namespace winrt::SDKTemplate::implementation
{
    Scenario1::Scenario1()
    {
        InitializeComponent();

        // I want this page to be always cached so that we don't have to add logic to save/restore state for the checkbox.
        NavigationCacheMode(Windows::UI::Xaml::Navigation::NavigationCacheMode::Required);
    }

    void Scenario1::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    void Scenario1::Button_Click(IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto rootFrame = Windows::UI::Xaml::Window::Current().Content().as<Windows::UI::Xaml::Controls::Frame>();

        // Navigate to the next page, with info in the parameters whether to enable the title bar UI or not.
        rootFrame.Navigate(xaml_typename<SDKTemplate::SecondaryPage>(), box_value(optedIn_));
    }

    void Scenario1::CheckBox_Toggle(IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        optedIn_ = !optedIn_;
    }
}
