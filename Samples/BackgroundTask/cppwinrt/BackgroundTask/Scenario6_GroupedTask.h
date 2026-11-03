#pragma once
#include "GroupedBackgroundTask.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct GroupedBackgroundTask : GroupedBackgroundTaskT<GroupedBackgroundTask>
    {
        GroupedBackgroundTask() = default;

        void UnregisterUngroupedTasks(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void RegisterGroupedBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterGroupedTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct GroupedBackgroundTask : GroupedBackgroundTaskT<GroupedBackgroundTask, implementation::GroupedBackgroundTask>
    {
    };
}
