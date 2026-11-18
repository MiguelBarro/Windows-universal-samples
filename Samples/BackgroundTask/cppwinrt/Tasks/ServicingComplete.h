#pragma once
#include "ServicingComplete.g.h"

namespace winrt::Tasks::implementation
{
    struct ServicingComplete : ServicingCompleteT<ServicingComplete>
    {
        using IBackgroundTaskInstance = Windows::ApplicationModel::Background::IBackgroundTaskInstance;
        using BackgroundTaskCancellationReason
            = Windows::ApplicationModel::Background::BackgroundTaskCancellationReason;
        using LoggingChannel = Windows::Foundation::Diagnostics::LoggingChannel;

        ServicingComplete() = default;

        void Run(IBackgroundTaskInstance const& taskInstance);
        void OnCanceled(IBackgroundTaskInstance const& sender, BackgroundTaskCancellationReason const& reason);

    private:
        IBackgroundTaskInstance::Canceled_revoker _revoker;
        LoggingChannel _logger { winrt::get_class_name(*this) };
        std::atomic_bool _cancelRequested { false };
    };
}
namespace winrt::Tasks::factory_implementation
{
    struct ServicingComplete : ServicingCompleteT<ServicingComplete, implementation::ServicingComplete>
    {
    };
}
