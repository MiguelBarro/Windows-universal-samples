#include "pch.h"

#include "Scenario3_XmlLoading.h"

#include <regex>

#include "SampleConfiguration.h"
#include "Scenario3_XmlLoading.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario3_XmlLoading::Scenario3_XmlLoading()
    {
        InitializeComponent();
        Scenario3Init();
    }

    void Scenario3_XmlLoading::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    winrt::fire_and_forget Scenario3_XmlLoading::LaunchUri(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&) try
    {
        auto button = static_cast<winrt::Windows::UI::Xaml::Controls::HyperlinkButton const&>(sender);
        auto uri = winrt::Windows::Foundation::Uri(winrt::unbox_value<winrt::hstring>(button.Tag()));

        winrt::Windows::System::LauncherOptions options;
        co_await Windows::System::Launcher::LaunchUriAsync(uri, options);
    }
    catch (hresult_error const& e)
    {
        RichEditBoxSetError(scenario3Result(), e.message());
    }

    winrt::fire_and_forget Scenario3_XmlLoading::Scenario3Init() try
    {
        auto doc = co_await LoadXmlFile(L"loadExternaldtd", L"xmlWithExternaldtd.xml");
        RichEditBoxSetMsg(scenario3OriginalData(), doc.GetXml(), true);
    }
    catch (hresult_error const&)
    {
        RichEditBoxSetError(scenario3Result(), L"Exception occured while loading xml file!");
    }

    winrt::fire_and_forget Scenario3_XmlLoading::Scenario3BtnBuffer_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&) try
    {
        // Get load settings
        winrt::Windows::Data::Xml::Dom::XmlLoadSettings loadSettings;
        if (scenario3RB1().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(true);        // DTD is prohibited
            loadSettings.ResolveExternals(false);  // Disable the resolve to external definitions such as external DTD
        }
        else if (scenario3RB2().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(false);       // DTD is not prohibited
            loadSettings.ResolveExternals(false);  // Disable the resolve to external definitions such as external DTD
        }
        else if (scenario3RB3().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(false);       // DTD is not prohibited
            loadSettings.ResolveExternals(true);   // Enable the resolve to external definitions such as external DTD
        }

        winrt::hstring xml;
        scenario3OriginalData().Document().GetText(
                winrt::Windows::UI::Text::TextGetOptions::None,
                xml);

        // Set external dtd file path
        if (loadSettings.ResolveExternals() && !loadSettings.ProhibitDtd())
        {
            auto storageFolder =
                co_await Windows::ApplicationModel::Package::Current().InstalledLocation().GetFolderAsync(L"loadExternaldtd");
            std::wstring dtdPath (storageFolder.Path() + L"\\dtd.txt"), output;
            std::regex_replace(std::back_inserter(output), xml.begin(), xml.end(), std::wregex(L"dtd.txt"), dtdPath);
            xml = output;
        }

        winrt::Windows::Storage::Streams::DataWriter dataWriter;
        dataWriter.WriteString(xml);
        auto ibuffer = dataWriter.DetachBuffer();
        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXmlFromBuffer(ibuffer, loadSettings);
        RichEditBoxSetMsg(scenario3Result(), doc.GetXml(), true);
    }
    catch (hresult_error const&)
    {
        // After loadSettings.ProhibitDtd is set to true, the exception is expected as the sample XML contains DTD
        RichEditBoxSetError(scenario3Result(), L"Error: DTD is prohibited");
    }

    winrt::fire_and_forget Scenario3_XmlLoading::Scenario3BtnFile_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&) try
    {
        // Get load settings
        winrt::Windows::Data::Xml::Dom::XmlLoadSettings loadSettings;
        if (scenario3RB1().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(true);        // DTD is prohibited
            loadSettings.ResolveExternals(false);  // Disable the resolve to external definitions such as external DTD
        }
        else if (scenario3RB2().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(false);       // DTD is not prohibited
            loadSettings.ResolveExternals(false);  // Disable the resolve to external definitions such as external DTD
        }
        else if (scenario3RB3().IsChecked().Value())
        {
            loadSettings.ProhibitDtd(false);       // DTD is not prohibited
            loadSettings.ResolveExternals(true);   // Enable the resolve to external definitions such as external DTD
        }

        auto folder =
            co_await Windows::ApplicationModel::Package::Current().InstalledLocation().GetFolderAsync(L"loadExternaldtd");
        auto file = co_await folder.GetFileAsync(L"xmlWithExternaldtd.xml");
        auto doc = co_await Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(file, loadSettings);

        RichEditBoxSetMsg(scenario3Result(), doc.GetXml(), true);
    }
    catch (hresult_error const&)
    {
        // After loadSettings.ProhibitDtd is set to true, the exception is expected as the sample XML contains DTD
        RichEditBoxSetError(scenario3Result(), L"Error: DTD is prohibited");
    }
}
