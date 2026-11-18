#include "pch.h"
#include "Scenario3_ServicingCompleteTask.h"
#include "ServicingCompleteTask.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    ServicingCompleteTask::ServicingCompleteTask()
    {
        InitializeComponent();
    }

    void ServicingCompleteTask::OnNavigatedTo(
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

    fire_and_forget ServicingCompleteTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        auto task = co_await BackgroundTaskSample::RegisterBackgroundTask(
            SystemTrigger(SystemTriggerType::ServicingComplete, false),
            nullptr);

        AttachProgressAndCompletedHandlers(task);
        UpdateUI();
    }

    void ServicingCompleteTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        UpdateBackgroundTaskProgress(L"Disabled");
        UpdateUI();
    }

    void ServicingCompleteTask::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &ServicingCompleteTask::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &ServicingCompleteTask::OnCompleted });
    }

    fire_and_forget ServicingCompleteTask::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void ServicingCompleteTask::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget ServicingCompleteTask::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        Progress().Text(GetBackgroundTaskProgress());
        Status().Text(GetBackgroundTaskStatus());
    }
}
