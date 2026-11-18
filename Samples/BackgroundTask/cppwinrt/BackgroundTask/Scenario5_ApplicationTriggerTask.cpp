#include "pch.h"
#include "Scenario5_ApplicationTriggerTask.h"
#include "ApplicationTriggerTask.g.cpp"
#include "Utils.h"

namespace winrt::SDKTemplate::implementation
{
    ApplicationTriggerTask::ApplicationTriggerTask()
    {
        InitializeComponent();
    }

    void ApplicationTriggerTask::OnNavigatedTo(
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

        // Create a new ApplicationTrigger to use for signaling the background task.
        _trigger = Windows::ApplicationModel::Background::ApplicationTrigger();

        UpdateUI();
    }

    fire_and_forget ApplicationTriggerTask::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto task = co_await BackgroundTaskSample::RegisterBackgroundTask(_trigger, nullptr);

        AttachProgressAndCompletedHandlers(task);
        UpdateUI();
    }

    void ApplicationTriggerTask::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        UpdateBackgroundTaskProgress(L"Disabled");
        UpdateUI();
    }

    fire_and_forget ApplicationTriggerTask::SignalBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
        {
            //Signal the ApplicationTrigger
            auto result = co_await _trigger.RequestAsync();
            _result = L"Signal result: " + to_hstring(result);
            UpdateUI();
        }

    void ApplicationTriggerTask::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &ApplicationTriggerTask::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &ApplicationTriggerTask::OnCompleted });
    }

    fire_and_forget ApplicationTriggerTask::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void ApplicationTriggerTask::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget ApplicationTriggerTask::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        SignalButton().IsEnabled(GetBackgroundTaskRegistrationStatus() && _trigger);
        Progress().Text(GetBackgroundTaskProgress());
        Result().Text(_result);
        Status().Text(GetBackgroundTaskStatus());
    }
}
