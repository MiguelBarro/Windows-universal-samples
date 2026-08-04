#include "pch.h"

#include "Scenario5_XSLTTransform.h"

#include "SampleConfiguration.h"
#include "Scenario5_XSLTTransform.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario5_XSLTTransform::Scenario5_XSLTTransform()
    {
        InitializeComponent();
        Scenario5Init();
    }

    winrt::fire_and_forget Scenario5_XSLTTransform::Scenario5Init() try
    {
        auto storageFolder =
            co_await Windows::ApplicationModel::Package::Current().InstalledLocation().GetFolderAsync(L"xsltTransform");
        auto xmlFile = co_await storageFolder.GetFileAsync(L"xmlContent.xml");
        auto xsltFile = co_await storageFolder.GetFileAsync(L"xslContent.xml");

        // load xml file
        auto doc = co_await winrt::Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(xmlFile);
        RichEditBoxSetMsg(scenario5Xml(), doc.GetXml(), false);

        // load xslt file
        doc = co_await winrt::Windows::Data::Xml::Dom::XmlDocument::LoadFromFileAsync(xsltFile);

        // Display xml and xslt file content in the input fields
        RichEditBoxSetMsg(scenario5Xslt(), doc.GetXml(), false);
        RichEditBoxSetMsg(scenario5Result(), {}, true);
    }
    catch (hresult_error const& e)
    {
        RichEditBoxSetMsg(scenario5Xml(), {}, false);
        RichEditBoxSetMsg(scenario5Xslt(), {}, false);
        RichEditBoxSetError(scenario5Result(), e.message());
        rootPage_.NotifyUser(L"Exception occured while loading xml file!", NotifyType::ErrorMessage);
    }

    void Scenario5_XSLTTransform::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    void Scenario5_XSLTTransform::Scenario5BtnTransformToString_Click(
            winrt::Windows::Foundation::IInspectable,
            winrt::Windows::UI::Xaml::RoutedEventArgs)
    {
        scenario5Xml().Foreground(winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::White()));
        scenario5Xslt().Foreground(winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::White()));
        RichEditBoxSetMsg(scenario5Result(), {}, true);

        winrt::hstring xml, xslt;

        // Get xml content from xml input field
        scenario5Xml().Document().GetText(Windows::UI::Text::TextGetOptions::None, xml);

        // Get xslt content from xslt input field
        scenario5Xslt().Document().GetText(Windows::UI::Text::TextGetOptions::None, xslt);

        if (xml.empty())
        {
            RichEditBoxSetError(scenario5Result(), L"Source XML can't be empty");
            return;
        }

        if (xslt.empty())
        {
            RichEditBoxSetError(scenario5Result(), L"XSL content can't be empty");
            return;
        }

        winrt::Windows::Data::Xml::Dom::XmlDocument doc, xsltDoc;

        try
        {
            // Load xml content
            doc.LoadXml(xml);
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }

        try
        {
            // Load xslt content
            xsltDoc.LoadXml(xslt);
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }

        try
        {
            // Transform xml according to the style sheet declaration specified in xslt file
            winrt::Windows::Data::Xml::Xsl::XsltProcessor xsltProcessor(xsltDoc);
            auto transformedStr = xsltProcessor.TransformToString(doc);
            RichEditBoxSetError(scenario5Result(), transformedStr);
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }
    }

    winrt::fire_and_forget Scenario5_XSLTTransform::Scenario5BtnTransformToDocument_Click(
            winrt::Windows::Foundation::IInspectable,
            winrt::Windows::UI::Xaml::RoutedEventArgs)
    {
        scenario5Xml().Foreground(winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::White()));
        scenario5Xslt().Foreground(winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::White()));
        RichEditBoxSetMsg(scenario5Result(), {}, true);

        winrt::hstring xml, xslt;

        // Get xml content from xml input field
        scenario5Xml().Document().GetText(Windows::UI::Text::TextGetOptions::None, xml);

        // Get xslt content from xslt input field
        scenario5Xslt().Document().GetText(Windows::UI::Text::TextGetOptions::None, xslt);

        if (xml.empty())
        {
            RichEditBoxSetError(scenario5Result(), L"Source XML can't be empty");
            co_return;
        }

        if (xslt.empty())
        {
            RichEditBoxSetError(scenario5Result(), L"XSL content can't be empty");
            co_return;
        }

        winrt::Windows::Data::Xml::Dom::XmlDocument doc, xsltDoc;

        try
        {
            // Load xml content
            doc.LoadXml(xml);
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }

        try
        {
            // Load xslt content
            xsltDoc.LoadXml(xslt);
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }

        try
        {
            // Transform xml according to the style sheet declaration specified in xslt file
            winrt::Windows::Data::Xml::Xsl::XsltProcessor xsltProcessor(xsltDoc);
            auto transformedDocument = xsltProcessor.TransformToDocument(doc);
            auto storageFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
            auto xmlFile = co_await storageFolder.CreateFileAsync(
                    L"transformed.html",
                    winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting);
            co_await transformedDocument.SaveToFileAsync(xmlFile);

            RichEditBoxSetError(scenario5Result(), L"The result has been save to: " + xmlFile.Path());
        }
        catch (hresult_error const& e)
        {
            scenario5Xml().Foreground(
                    winrt::Windows::UI::Xaml::Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
            RichEditBoxSetError(scenario5Result(), e.message());
        }
    }
}
