#pragma once
#include "SampleBackgroundTask.g.h"

#include "Scenario1_SampleBackgroundTask.xaml.g.h"

#include "BackgroundTaskSample.h"

namespace winrt::SDKTemplate::implementation
{
    struct SampleBackgroundTask
        : SampleBackgroundTaskT<SampleBackgroundTask>
        , BackgroundTaskSample<L"SampleBackgroundTask", L"Tasks.SampleBackgroundTask", false>
    {
        SampleBackgroundTask();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        fire_and_forget RegisterBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterBackgroundTask(
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
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration::Progress_revoker _progressRevoker;
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration::Completed_revoker _completedRevoker;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask, implementation::SampleBackgroundTask>
    {
    };
}
