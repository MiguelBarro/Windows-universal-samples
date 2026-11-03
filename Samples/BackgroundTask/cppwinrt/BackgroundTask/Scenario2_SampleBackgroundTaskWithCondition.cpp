#include "pch.h"
#include "Scenario2_SampleBackgroundTaskWithCondition.h"
#include "SampleBackgroundTaskWithCondition.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void SampleBackgroundTaskWithCondition::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void SampleBackgroundTaskWithCondition::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
