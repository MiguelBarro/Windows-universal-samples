#pragma once

#include <algorithm>
#include <string>
#include <string_view>

#include <hstring.h>

#include <winrt/Windows.ApplicationModel.Background.h>
#include <winrt/Windows.Storage.h>

namespace winrt::SDKTemplate
{
    // P0732R2: C++20 feature
    template<size_t N>
    struct StringLiteral
    {
        wchar_t value[N];

        constexpr StringLiteral(const wchar_t(&str)[N]) {
            std::copy_n(str, N, value);
        }

        constexpr operator const wchar_t* () const
        {
            return value;
        }
    };

    template<
        StringLiteral taskName,
        StringLiteral taskEntryPoint,
        bool backgroundAccessRequired>
    struct BackgroundTaskSample
    {
        using BackgroundTaskRegistration = Windows::ApplicationModel::Background::BackgroundTaskRegistration;
        using BackgroundTaskRegistrationGroup = Windows::ApplicationModel::Background::BackgroundTaskRegistrationGroup;
        using IBackgroundTrigger = Windows::ApplicationModel::Background::IBackgroundTrigger;
        using IBackgroundCondition = Windows::ApplicationModel::Background::IBackgroundCondition;

        static Windows::Foundation::IAsyncOperation<BackgroundTaskRegistration>
        RegisterBackgroundTask(
                IBackgroundTrigger const& trigger,
                IBackgroundCondition const& condition,
                BackgroundTaskRegistrationGroup group = {nullptr})
        {
            using namespace Windows::ApplicationModel::Background;

            auto cancel = co_await get_cancellation_token();
            cancel.enable_propagation();

            if (_backgroundAccessRequired)
            {
                // If the user denies access, the task will not run.
                auto requestTask = co_await BackgroundExecutionManager::RequestAccessAsync();
                switch (requestTask)
                {
                    case BackgroundAccessStatus::Denied:
                        throw hresult_error(E_ACCESSDENIED, L"Background access denied.");
                    case BackgroundAccessStatus::DeniedBySystemPolicy:
                        throw hresult_error(E_ACCESSDENIED, L"Background access denied by system policy.");
                    case BackgroundAccessStatus::DeniedByUser:
                        throw hresult_error(E_ACCESSDENIED, L"Background access denied by user.");
                }
            }

            BackgroundTaskBuilder builder;

            builder.Name(_taskName);
            builder.TaskEntryPoint(_taskEntryPoint);
            builder.SetTrigger(trigger);

            if (condition)
            {
                builder.AddCondition(condition);

                //
                // If the condition changes while the background task is executing then it will
                // be canceled.
                //
                builder.CancelOnConditionLoss(true);
            }

            if (group)
            {
                builder.TaskGroup(group);
            }

            auto task = builder.Register();

            UpdateBackgroundTaskRegistrationStatus(true);

            //
            // Remove previous completion status. Registration Status must persist.
            //
            Windows::Storage::ApplicationData::Current().LocalSettings().Values().TryRemove(_taskProgressKey);

            co_return task;
        }

        static void UnregisterBackgroundTasks(BackgroundTaskRegistrationGroup group = {nullptr})
        {
            if (group)
            {
                for (auto task : group.AllTasks())
                {
                    if (task.Value().Name() == _taskName)
                    {
                        task.Value().Unregister(true);
                        UpdateBackgroundTaskRegistrationStatus(false);
                    }
                }
            }
            else
            {
                //
                // Loop through all ungrouped background tasks and unregister any with the given name.
                //
                for (auto task : BackgroundTaskRegistration::AllTasks())
                {
                    if (task.Value().Name() == _taskName)
                    {
                        task.Value().Unregister(true);
                        UpdateBackgroundTaskRegistrationStatus(false);
                    }
                }
            }
        }

        static BackgroundTaskRegistrationGroup GetTaskGroup(
                hstring id,
                hstring groupName)
        {
            auto group = BackgroundTaskRegistration::GetTaskGroup(id);

            if (!group)
            {
                group = BackgroundTaskRegistrationGroup::CreateGroup(groupName);
            }

            return group;
        }

        static void UpdateBackgroundTaskRegistrationStatus(bool registered)
        {
            auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
            settings.Values().Insert(_taskRegisteredKey, box_value(registered));
        }

        static bool GetBackgroundTaskRegistrationStatus()
        {
            auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
            auto registered = settings.Values().TryLookup(_taskRegisteredKey);
            return registered ? unbox_value<bool>(registered) : false;
        }

        static void UpdateBackgroundTaskProgress(const std::wstring_view progress)
        {
            auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
            settings.Values().Insert(_taskProgressKey, box_value(progress));
        }

        static const std::wstring GetBackgroundTaskProgress()
        {
            auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
            auto taskProgress = settings.Values().TryLookup(_taskProgressKey);
            return taskProgress ? unbox_value<hstring>(taskProgress).c_str() : L"0";
        }

        static std::wstring GetBackgroundTaskStatus()
        {
            std::wstring status = GetBackgroundTaskRegistrationStatus() ? L"Registered" : L"Unregistered";
            status += L" - " + GetBackgroundTaskProgress();
            return status;
        }

        static bool TaskRequiresBackgroundAccess()
        {
            return _backgroundAccessRequired;
        }

        static constexpr std::wstring_view TaskName()
        {
            return _taskName;
        }

        static constexpr std::wstring_view TaskEntryPoint()
        {
            return _taskEntryPoint;
        }

    private:
        inline static const std::wstring _taskName {taskName};
        inline static const std::wstring _taskEntryPoint {taskEntryPoint};
        inline static const bool _backgroundAccessRequired {backgroundAccessRequired};

        inline static const std::wstring _taskRegisteredKey { _taskName + L"Registered" };
        inline static const std::wstring _taskProgressKey { _taskName + L"Progress" };
    };
} // namespace winrt::SDKTemplate
