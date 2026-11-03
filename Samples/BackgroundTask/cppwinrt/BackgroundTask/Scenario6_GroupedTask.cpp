#include "pch.h"
#include "Scenario6_GroupedTask.h"
#include "GroupedBackgroundTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void GroupedBackgroundTask::UnregisterUngroupedTasks(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void GroupedBackgroundTask::RegisterGroupedBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void GroupedBackgroundTask::UnregisterGroupedTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
