#include "pch.h"
#include "Scenario5_ApplicationTriggerTask.h"
#include "ApplicationTriggerTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void ApplicationTriggerTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void ApplicationTriggerTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void ApplicationTriggerTask::SignalBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
