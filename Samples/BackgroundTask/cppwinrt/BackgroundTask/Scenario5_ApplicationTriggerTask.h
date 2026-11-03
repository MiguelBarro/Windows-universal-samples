#pragma once
#include "ApplicationTriggerTask.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct ApplicationTriggerTask : ApplicationTriggerTaskT<ApplicationTriggerTask>
    {
        ApplicationTriggerTask() = default;

        void RegisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void SignalBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct ApplicationTriggerTask : ApplicationTriggerTaskT<ApplicationTriggerTask, implementation::ApplicationTriggerTask>
    {
    };
}
