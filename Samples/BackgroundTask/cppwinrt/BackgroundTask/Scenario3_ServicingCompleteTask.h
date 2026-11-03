#pragma once
#include "ServicingCompleteTask.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct ServicingCompleteTask : ServicingCompleteTaskT<ServicingCompleteTask>
    {
        ServicingCompleteTask() = default;

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
    struct ServicingCompleteTask : ServicingCompleteTaskT<ServicingCompleteTask, implementation::ServicingCompleteTask>
    {
    };
}
