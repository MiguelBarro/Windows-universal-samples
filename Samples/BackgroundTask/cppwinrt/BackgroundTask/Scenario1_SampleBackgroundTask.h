#pragma once
#include "SampleBackgroundTask.g.h"
#include "Scenario1_SampleBackgroundTask.xaml.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask>
    {
        SampleBackgroundTask() = default;

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
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask, implementation::SampleBackgroundTask>
    {
    };
}
