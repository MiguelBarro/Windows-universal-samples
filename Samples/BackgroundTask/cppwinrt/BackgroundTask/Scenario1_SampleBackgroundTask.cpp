#include "pch.h"
#include "Scenario1_SampleBackgroundTask.h"
#include "SampleBackgroundTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void SampleBackgroundTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void SampleBackgroundTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
