#include "pch.h"
#include "Scenario6_GroupedTask.h"
#include "GroupedBackgroundTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    GroupedBackgroundTask::GroupedBackgroundTask()
    {
        InitializeComponent();
    }

    void GroupedBackgroundTask::OnNavigatedTo(
            Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        _group = BackgroundTaskRegistration::GetTaskGroup(_groupId);

        if (!_group)
            _group = BackgroundTaskRegistrationGroup(_groupId, _groupName);

        for (auto task : _group.AllTasks())
        {
            if (task.Value().Name() == TaskName())
            {
                AttachProgressAndCompletedHandlers(task.Value());
                UpdateBackgroundTaskRegistrationStatus(true);
                break;
            }
        }

        UpdateUI();
    }

    fire_and_forget GroupedBackgroundTask::RegisterGroupedBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        auto task = co_await BackgroundTaskSample::RegisterBackgroundTask(
            SystemTrigger(SystemTriggerType::TimeZoneChange, false),
            nullptr,
            _group);

        AttachProgressAndCompletedHandlers(task);
        UpdateUI();
    }

    void GroupedBackgroundTask::UnregisterGroupedTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks(_group);

        if (!GetBackgroundTaskRegistrationStatus())
            UpdateBackgroundTaskProgress(L"Disabled");

        UpdateUI();
    }

    void GroupedBackgroundTask::UnregisterUngroupedTasks(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        if (!GetBackgroundTaskRegistrationStatus())
            UpdateBackgroundTaskProgress(L"Disabled");

        UpdateUI();
    }

    void GroupedBackgroundTask::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &GroupedBackgroundTask::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &GroupedBackgroundTask::OnCompleted });
    }

    fire_and_forget GroupedBackgroundTask::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void GroupedBackgroundTask::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget GroupedBackgroundTask::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterGroupedButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        Progress().Text(GetBackgroundTaskProgress());
        Status().Text(GetBackgroundTaskStatus());
    }
}
