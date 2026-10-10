#include "pch.h"
#include "Scenario_Suspension.h"
#include "Scenario_Suspension.g.cpp"

#include "Item.h"
#include "ItemClickEventArgs.h"

namespace winrt::SDKTemplate::implementation
{
    // static member to propagate App termination info after launching the app again
    bool Scenario_Suspension::lastSessionTerminated = false;

    // static method to allow SubPages to access the Scenario
    weak_ref<Scenario_Suspension> Scenario_Suspension::navigationInstance;

    Scenario_Suspension::Scenario_Suspension()
    {
        InitializeComponent();

        if (lastSessionTerminated)
        {
            [](SDKTemplate::Scenario_Suspension me) -> winrt::fire_and_forget
            {
                // The app was terminated after being suspended. Restore the previous state.
                Windows::Storage::StorageFile file {nullptr};
                file = co_await Windows::Storage::ApplicationData::Current().LocalFolder().GetFileAsync(sessionStateFilename);
                Windows::Data::Json::JsonObject state =
                        Windows::Data::Json::JsonObject::Parse(co_await Windows::Storage::FileIO::ReadTextAsync(file));
                me.RestoreState(state);
            }(*this);
        }
        else
        {
            // Populate the ItemList with some default items.
            for (int i = 0; i < 5; ++i)
                AddItem();
        }

        // Associate the ListView control with the ItemList instance.
        list().ItemsSource(_items);

        // Register for the Suspending event. This event is raised when the app is being suspended.
        _revoker = Windows::UI::Xaml::Application::Current().Suspending(
                auto_revoke_t {},
                {this, &Scenario_Suspension::OnSuspending}
                );

        // Register for keyboard accelerators.
        _keyRevoker = Windows::UI::Xaml::Window::Current()
            .CoreWindow().Dispatcher().AcceleratorKeyActivated(
                    auto_revoke_t{},
                    {this, &Scenario_Suspension::OnAcceleratorKeyActivated});

        // Register mouse feedback
        _mouseRevoker = Windows::UI::Xaml::Window::Current()
            .CoreWindow().PointerPressed(
                    auto_revoke_t{},
                    {this, &Scenario_Suspension::OnMousePointerPressed});
    }

    Windows::Foundation::Collections::IObservableVector<SDKTemplate::Item> Scenario_Suspension::Items()
    {
        return _items;
    }

    void Scenario_Suspension::ListView_ItemClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        // Update the current index
        uint32_t current;
        _items.IndexOf(e.ClickedItem().as<SDKTemplate::Item>(), current);
        _current = current;

        // Move to the subpage
        navigationInstance = get_weak();
        Frame().Navigate(winrt::xaml_typename<SDKTemplate::SubPage>(), box_value(current));
    }

    void Scenario_Suspension::AddItem()
    {
        _items.Append(winrt::make<Item>(L"Item " + std::to_wstring(_items.Size() + 1)));
    }

    void Scenario_Suspension::ResetItems()
    {
        _items.Clear();
        _current.reset();
        // Associate the ListView control with the new ItemList instance.
        list().ItemsSource(_items);
    }

    Windows::Data::Json::JsonObject Scenario_Suspension::SaveState() const
    {
        Windows::Data::Json::JsonObject state;

        Windows::Data::Json::JsonArray itemsArray;
        for (const auto& item : _items)
        {
            itemsArray.Append(item.ToJsonObject());
        }

        // Save current Page if any
        if (_current)
            state.SetNamedValue(
                    currentPropertyName,
                    Windows::Data::Json::JsonValue::CreateNumberValue(_current.value())
                    );

        // Save all pages
        state.SetNamedValue(itemsPropertyName, itemsArray);

        // Save navigation info
        state.SetNamedValue(
                navigationPropertyName,
                Windows::Data::Json::JsonValue::CreateStringValue(Frame().GetNavigationState())
                );

        return state;
    }

    void Scenario_Suspension::RestoreState(Windows::Data::Json::JsonObject state)
    {
        ResetItems();

        // Restore Pages
        if (state.HasKey(itemsPropertyName))
        {
            Windows::Data::Json::JsonArray itemsArray = state.GetNamedArray(itemsPropertyName);
            for (const auto& itemValue : itemsArray)
            {
                _items.Append(SDKTemplate::Item(itemValue.GetObject()));
            }
        }

        // Restore current Page if any
        if (state.HasKey(currentPropertyName))
        {
            _current = static_cast<uint32_t>(state.GetNamedNumber(currentPropertyName));
            ListView_ItemClick(
                    nullptr,
                    make<Windows::UI::Xaml::Controls::implementation::ItemClickEventArgs>(
                            _items.GetAt(_current.value()),
                            nullptr)
                    );
        }

        // Restore navigation info
        if (state.HasKey(navigationPropertyName))
        {
            Frame().SetNavigationState(state.GetNamedString(navigationPropertyName));
        }
    }

    fire_and_forget Scenario_Suspension::OnSuspending(
            Windows::Foundation::IInspectable const& sender,
            Windows::ApplicationModel::SuspendingEventArgs const& args) const
    {
        // Save the current state of the app in case the process is terminated while the app is suspended.
        Windows::Data::Json::JsonObject state = SaveState();
        Windows::Storage::StorageFile file {nullptr};
        file = co_await Windows::Storage::ApplicationData::Current().LocalFolder()
                .CreateFileAsync(sessionStateFilename, Windows::Storage::CreationCollisionOption::ReplaceExisting);
        co_await Windows::Storage::FileIO::WriteTextAsync(file, state.Stringify());
    }

    void Scenario_Suspension::OnAcceleratorKeyActivated(
            Windows::UI::Core::CoreDispatcher const&,
            Windows::UI::Core::AcceleratorKeyEventArgs const& e) const
    {
        using namespace Windows::UI::Core;
        using namespace Windows::System;

        auto virtualKey = e.VirtualKey();
        auto eventType = e.EventType();

        // Only investigate further when Left, Right, or the dedicated Previous or Next keys are pressed
        if((eventType == CoreAcceleratorKeyEventType::SystemKeyDown ||
            eventType == CoreAcceleratorKeyEventType::KeyDown) &&
           (virtualKey == VirtualKey::Left || virtualKey == VirtualKey::Right ||
           virtualKey == VirtualKey::GoBack || virtualKey == VirtualKey::GoForward))
        {
            auto coreWindow = Windows::UI::Xaml::Window::Current().CoreWindow();
            auto downState = CoreVirtualKeyStates::Down;
            bool menuKey = (coreWindow.GetKeyState(VirtualKey::Menu) & downState) == downState;
            bool controlKey = (coreWindow.GetKeyState(VirtualKey::Control) & downState) == downState;
            bool shiftKey = (coreWindow.GetKeyState(VirtualKey::Shift) & downState) == downState;
            bool noModifiers = !menuKey && !controlKey && !shiftKey;
            bool onlyAlt = menuKey && !controlKey && !shiftKey;

            if ((virtualKey == VirtualKey::GoBack && noModifiers) ||
                (virtualKey == VirtualKey::Left && onlyAlt))
            {
                if (Frame().CanGoBack())
                {
                    Frame().GoBack();
                    e.Handled(true);
                }
            }
            else if ((virtualKey == VirtualKey::GoForward && noModifiers) ||
                (virtualKey == VirtualKey::Right && onlyAlt))
            {
                if (Frame().CanGoForward())
                {
                    Frame().GoForward();
                    e.Handled(true);
                }
            }
        }
    }

    void Scenario_Suspension::OnMousePointerPressed(
            Windows::UI::Core::ICoreWindow const&,
            Windows::UI::Core::PointerEventArgs const& e) const
    {
        auto properties = e.CurrentPoint().Properties();

        // Ignore button chords with the left, right, and middle buttons
        if (properties.IsLeftButtonPressed() || properties.IsRightButtonPressed() ||
            properties.IsMiddleButtonPressed())
            return;

            // If back or foward are pressed (but not both) navigate appropriately
            bool backPressed = properties.IsXButton1Pressed();
            bool forwardPressed = properties.IsXButton2Pressed();
            if (backPressed ^ forwardPressed)
            {
                e.Handled(true);
                if (backPressed)
                    Frame().GoBack();
                if (forwardPressed)
                    Frame().GoForward();
            }
    }
}
