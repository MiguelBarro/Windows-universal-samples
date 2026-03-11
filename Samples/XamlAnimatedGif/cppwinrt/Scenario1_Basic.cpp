#include "pch.h"
#include "Scenario1_Basic.h"
#include "Scenario1_Basic.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario1_Basic::Scenario1_Basic()
    {
        InitializeComponent();
    }

    void Scenario1_Basic::ClickToPlaySource_ImageOpened(IInspectable const&, Windows::UI::Xaml::RoutedEventArgs const&)
    {
        // Once ImageOpened is raised, we can query whether an image is animated.
        if(ClickToPlaySource().IsAnimatedBitmap())
        {
            PlaybackButtons().Visibility(Windows::UI::Xaml::Visibility::Visible);
        }
    }
}
