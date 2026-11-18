#pragma once
#include "ApplicationTriggerTask.g.h"

#include "Scenario5_ApplicationTriggerTask.xaml.g.h"

#include "BackgroundTaskSample.h"

#include <string>

namespace winrt::SDKTemplate::implementation
{
    struct ApplicationTriggerTask
        : ApplicationTriggerTaskT<ApplicationTriggerTask>
        , BackgroundTaskSample<L"ApplicationTriggerTask", L"Tasks.SampleBackgroundTask", true>
    {
        ApplicationTriggerTask();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        fire_and_forget RegisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        fire_and_forget SignalBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void AttachProgressAndCompletedHandlers(
                Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task);

        fire_and_forget OnProgress(
                Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task,
                Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args);

        void OnCompleted(
                Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task,
                Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const& args);

        fire_and_forget UpdateUI();

    private:
        std::wstring _result;
        Windows::ApplicationModel::Background::ApplicationTrigger _trigger{ nullptr };
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration::Progress_revoker _progressRevoker;
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration::Completed_revoker _completedRevoker;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct ApplicationTriggerTask : ApplicationTriggerTaskT<ApplicationTriggerTask, implementation::ApplicationTriggerTask>
    {
    };
}
