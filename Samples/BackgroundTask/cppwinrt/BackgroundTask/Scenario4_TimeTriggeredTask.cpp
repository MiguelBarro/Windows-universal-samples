#include "pch.h"
#include "Scenario4_TimeTriggeredTask.h"
#include "TimeTriggeredTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    TimeTriggeredTask::TimeTriggeredTask()
    {
        InitializeComponent();
    }

    void TimeTriggeredTask::OnNavigatedTo(
            Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        for (auto task : BackgroundTaskRegistration::AllTasks())
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

    fire_and_forget TimeTriggeredTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        IBackgroundTaskRegistration task {nullptr};

        try
        {
            // may throw if the user has disabled background tasks for this app
            task = co_await BackgroundTaskSample::RegisterBackgroundTask(
                TimeTrigger(15, false),
                nullptr);

            AttachProgressAndCompletedHandlers(task);
            UpdateUI();
        }
        catch (hresult_error const& ex)
        {
            Status().Text(ex.message());
        }
    }

    void TimeTriggeredTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        UpdateBackgroundTaskProgress(L"Disabled");
        UpdateUI();
    }

    void TimeTriggeredTask::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &TimeTriggeredTask::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &TimeTriggeredTask::OnCompleted });
    }

    fire_and_forget TimeTriggeredTask::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void TimeTriggeredTask::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget TimeTriggeredTask::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        Progress().Text(GetBackgroundTaskProgress());
        Status().Text(GetBackgroundTaskStatus());
    }
}
