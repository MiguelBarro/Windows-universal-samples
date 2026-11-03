#include "pch.h"
#include "Scenario3_ServicingCompleteTask.h"
#include "ServicingCompleteTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    void ServicingCompleteTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }

    void ServicingCompleteTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        throw hresult_not_implemented();
    }
}
