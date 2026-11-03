#pragma once
#include "TimeTriggeredTask.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct TimeTriggeredTask : TimeTriggeredTaskT<TimeTriggeredTask>
    {
        TimeTriggeredTask() = default;

        void RegisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct TimeTriggeredTask : TimeTriggeredTaskT<TimeTriggeredTask, implementation::TimeTriggeredTask>
    {
    };
}
