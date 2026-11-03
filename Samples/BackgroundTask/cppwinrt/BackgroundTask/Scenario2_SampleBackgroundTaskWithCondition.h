#pragma once
#include "SampleBackgroundTaskWithCondition.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct SampleBackgroundTaskWithCondition : SampleBackgroundTaskWithConditionT<SampleBackgroundTaskWithCondition>
    {
        SampleBackgroundTaskWithCondition() = default;

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
    struct SampleBackgroundTaskWithCondition : SampleBackgroundTaskWithConditionT<SampleBackgroundTaskWithCondition, implementation::SampleBackgroundTaskWithCondition>
    {
    };
}
