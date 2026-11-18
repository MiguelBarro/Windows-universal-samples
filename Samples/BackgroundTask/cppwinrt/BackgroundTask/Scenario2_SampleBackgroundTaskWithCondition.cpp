#include "pch.h"
#include "Scenario2_SampleBackgroundTaskWithCondition.h"
#include "SampleBackgroundTaskWithCondition.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    SampleBackgroundTaskWithCondition::SampleBackgroundTaskWithCondition()
    {
        InitializeComponent();
    }

    void SampleBackgroundTaskWithCondition::OnNavigatedTo(
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

    fire_and_forget SampleBackgroundTaskWithCondition::RegisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace Windows::ApplicationModel::Background;

        auto task = co_await BackgroundTaskSample::RegisterBackgroundTask(
            SystemTrigger(SystemTriggerType::TimeZoneChange, false),
            SystemCondition(SystemConditionType::InternetAvailable));

        AttachProgressAndCompletedHandlers(task);
        UpdateUI();
    }

    void SampleBackgroundTaskWithCondition::UnregisterBackgroundTask(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Xaml::RoutedEventArgs const&)
    {
        UnregisterBackgroundTasks();

        UpdateBackgroundTaskProgress(L"Disabled");
        UpdateUI();
    }

    void SampleBackgroundTaskWithCondition::AttachProgressAndCompletedHandlers(
        Windows::ApplicationModel::Background::IBackgroundTaskRegistration const& task)
    {
        _progressRevoker = task.Progress(auto_revoke_t{}, { this, &SampleBackgroundTaskWithCondition::OnProgress });
        _completedRevoker = task.Completed(auto_revoke_t{}, { this, &SampleBackgroundTaskWithCondition::OnCompleted });
    }

    fire_and_forget SampleBackgroundTaskWithCondition::OnProgress(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskProgressEventArgs const& args)
    {
        auto lifetime = get_strong();
        auto const progress = args.Progress();

        co_await resume_foreground(Dispatcher());

        UpdateBackgroundTaskProgress(L"Progress: " + std::to_wstring(progress) + L"%");
        UpdateUI();
    }

    void SampleBackgroundTaskWithCondition::OnCompleted(
            Windows::ApplicationModel::Background::IBackgroundTaskRegistration const&,
            Windows::ApplicationModel::Background::BackgroundTaskCompletedEventArgs const&)
    {
        UpdateUI();
    }

    fire_and_forget SampleBackgroundTaskWithCondition::UpdateUI()
    {
        auto lifetime = get_strong();
        co_await resume_foreground(Dispatcher());

        RegisterButton().IsEnabled(!GetBackgroundTaskRegistrationStatus());
        UnregisterButton().IsEnabled(GetBackgroundTaskRegistrationStatus());
        Progress().Text(GetBackgroundTaskProgress());
        Status().Text(GetBackgroundTaskStatus());
    }
}
