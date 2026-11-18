#include "pch.h"
#include "ServicingComplete.h"
#include "ServicingComplete.g.cpp"

namespace winrt::Tasks::implementation
{
    void ServicingComplete::Run(IBackgroundTaskInstance const& taskInstance)
    {
        using namespace Windows::ApplicationModel::Background;
        using namespace Windows::Foundation::Diagnostics;

        _logger.LogMessage(
                L"ServicingComplete " + taskInstance.Task().Name() + L" starting...",
                LoggingLevel::Information);

        //
        // Associate a cancellation handler with the background task.
        //
        _revoker = taskInstance.Canceled(winrt::auto_revoke, { this, &ServicingComplete::OnCanceled });

        //
        // Do background task activity for servicing complete.
        //
        uint32_t Progress;
        for (Progress = 0; Progress <= 100; Progress += 10)
        {
            //
            // If the cancellation handler indicated that the task was canceled, stop doing the task.
            //
            if (_cancelRequested)
            {
                break;
            }

            //
            // Indicate progress to foreground application.
            //
            taskInstance.Progress(Progress);
        }

        //
        // Write to LocalSettings to indicate that this background task ran.
        //
        auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
        hstring status {(Progress < 100) ? L"Canceled" : L"Completed"};
        settings.Values().Insert(taskInstance.Task().Name(), winrt::box_value(status));

        _logger.LogMessage(
                L"ServicingComplete " + taskInstance.Task().Name() + L" Starting...",
                LoggingLevel::Information);
    }

    void ServicingComplete::OnCanceled(
            IBackgroundTaskInstance const& sender,
            BackgroundTaskCancellationReason const&)
    {
        using namespace Windows::Foundation::Diagnostics;

        //
        // Indicate that the background task is canceled.
        //
        _cancelRequested = true;

        _logger.LogMessage(
                L"ServicingComplete " + sender.Task().Name() + L" Cancel Requested...",
                LoggingLevel::Information);
    }
}
