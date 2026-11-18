#pragma once
#include "GroupedBackgroundTask.g.h"

#include "Scenario6_GroupedTask.xaml.g.h"

#include "BackgroundTaskSample.h"

namespace winrt::SDKTemplate::implementation
{
    struct GroupedBackgroundTask
        : GroupedBackgroundTaskT<GroupedBackgroundTask>
        , BackgroundTaskSample<L"GroupedBackgroundTask", L"Tasks.SampleBackgroundTask", false>
    {
        GroupedBackgroundTask();

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        fire_and_forget RegisterGroupedBackgroundTask(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterUngroupedTasks(
                Windows::Foundation::IInspectable const& p0,
                Windows::UI::Xaml::RoutedEventArgs const& p1);

        void UnregisterGroupedTask(
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

        Windows::ApplicationModel::Background::BackgroundTaskRegistrationGroup _group {nullptr};
        inline static constexpr std::wstring_view _groupId {L"3F2504E0-5F89-41D3-9A0C-0405E82C3333"};
        inline static constexpr std::wstring_view _groupName {L"Background Task Group"};
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct GroupedBackgroundTask : GroupedBackgroundTaskT<GroupedBackgroundTask, implementation::GroupedBackgroundTask>
    {
    };
}
