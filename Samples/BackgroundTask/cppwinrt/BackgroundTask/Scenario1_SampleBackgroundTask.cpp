#include "pch.h"
#include "Scenario1_SampleBackgroundTask.h"
#include "SampleBackgroundTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    SampleBackgroundTask::SampleBackgroundTask()
    {
        InitializeComponent();
    }

    void SampleBackgroundTask::OnNavigatedTo(
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

    fire_and_forget SampleBackgroundTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        auto task = co_await BackgroundTaskSample::RegisterBackgroundTask(
            SystemTrigger(SystemTriggerType::TimeZoneChange, false),
            nullptr);

        AttachProgressAndCompletedHandlers(task);
        UpdateUI();
    }

    void SampleBackgroundTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        UpdateBackgroundTaskProgress(L"Disabled");
        UpdateUI();
    }

    void SampleBackgroundTask::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &SampleBackgroundTask::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &SampleBackgroundTask::OnCompleted });
    }

    fire_and_forget SampleBackgroundTask::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void SampleBackgroundTask::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget SampleBackgroundTask::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        Progress().Text(GetBackgroundTaskProgress());
        Status().Text(GetBackgroundTaskStatus());
    }
}
