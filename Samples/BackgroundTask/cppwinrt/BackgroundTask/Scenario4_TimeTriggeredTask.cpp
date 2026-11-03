#include "pch.h"
#include "Scenario4_TimeTriggeredTask.h"
#include "TimeTriggeredTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void TimeTriggeredTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void TimeTriggeredTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
