#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    hstring MainPage::FEATURE_NAME()
    {
        return L"xBind Sample in C++/CX";
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::SDKTemplate::Scenario> MainPage::scenarios()
    {
        using winrt::SDKTemplate::Scenario;

        std::vector<Scenario> scenarios {
            {
                L"Basic Bindings",
                L"Demonstrates simple OneTime and OneWay bindings against a model. Buttons are provided to adjust the model which will cause the OneWay bindings against properties with notifications to update.",
                L"SDKTemplate.BasicTests"
            },
            {
                L"Other Bindings",
                L"Demonstrates a more complex set of bindings including TwoWay, Converters, TargetNullValue, FallbackValue and bindings used in a variety of places in markup.",
                L"SDKTemplate.OtherBindings"
            },
            {
                L"List & Templates",
                L"Demonstrates using bindings in data templates, consumed by a list and as the content template of a button. The templates are defined inline to the list, in the page's resources and in a seperate resource dictionary.",
                L"SDKTemplate.ListsAndTemplates"
            },
            {
                L"List phasing using x:Phase",
                L"Demonstrates using x:Phase to achieve incremenatal rendering of the list items.",
                L"SDKTemplate.PhasingTests"
            },
            {
                L"Event Binding",
                L"Demonstrates using x:Bind with Events",
                L"SDKTemplate.EventTests"
            },
            {
                L"Function Binding",
                L"Demonstrates using x:Bind to bind to functions which is an easier way to do value conversions than using IValueConverter",
                L"SDKTemplate.Functions"
            }
        };

        return winrt::single_threaded_observable_vector(std::move(scenarios));
    }

    void MainPage::OnNavigatedTo(
            winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        using namespace winrt::Windows::UI::Xaml;

        // Set the newly created itemCollection as the ListBox ItemSource.
        ScenarioControl().ItemsSource(MainPage::scenarios());
        int startingScenarioIndex;

        if (Window::Current().Bounds().Width < 640)
            startingScenarioIndex = -1;
        else
            startingScenarioIndex = 0;

        ScenarioControl().SelectedIndex(startingScenarioIndex);
        ScenarioControl().ScrollIntoView(ScenarioControl().SelectedItem());
    }

    void MainPage::ScenarioControl_SelectionChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        using namespace winrt::Windows::UI::Xaml;

        auto scenarioListBox = sender.try_as<Controls::ListBox>();
        auto item = scenarioListBox.SelectedItem().try_as<SDKTemplate::Scenario>();

        if (item)
        {
            // Clear the status block when changing scenarios
            NotifyUser({}, winrt::SDKTemplate::NotifyType::StatusMessage);

            // Navigate to the selected scenario.
            Windows::UI::Xaml::Interop::TypeName scenarioType {
                item.ClassName(),
                winrt::Windows::UI::Xaml::Interop::TypeKind::Custom
            };
            ScenarioFrame().Navigate(scenarioType, *this);

            if (Window::Current().Bounds().Width < 640)
            {
                Splitter().IsPaneOpen(false);
                StatusBorder().Visibility(Visibility::Collapsed);
            }
        }
    }

    void MainPage::Footer_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto uri = winrt::Windows::Foundation::Uri(
                unbox_value<hstring>(
                    sender.as<winrt::Windows::UI::Xaml::Controls::HyperlinkButton>().Tag()));
        Windows::System::Launcher::LaunchUriAsync(uri);
    }

    void MainPage::Button_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        Splitter().IsPaneOpen(!Splitter().IsPaneOpen());
        StatusBorder().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
    }

    void MainPage::NotifyUser(std::wstring_view strMessage, winrt::SDKTemplate::NotifyType type)
    {
        using namespace winrt::Windows::UI;
        using namespace winrt::Windows::UI::Xaml::Media;

        switch (type)
        {
        case winrt::SDKTemplate::NotifyType::StatusMessage:
            StatusBorder().Background(SolidColorBrush(Colors::Green()));
            break;
        case winrt::SDKTemplate::NotifyType::ErrorMessage:
            StatusBorder().Background(SolidColorBrush(Colors::Red()));
            break;
        default:
            break;
        }

        StatusBlock().Text(strMessage);
        // Collapse the StatusBlock if it has no text to conserve real estate.
        if (StatusBlock().Text().empty())
        {
            StatusPanel().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
        }
        else
        {
            StatusPanel().Visibility(Windows::UI::Xaml::Visibility::Visible);
        }
    }
}
