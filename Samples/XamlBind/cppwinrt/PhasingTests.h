#pragma once
#include "FileItem.g.h"
#include "PhasingTests.g.h"
#include "winrt/xBindSampleModel.h"

namespace winrt::SDKTemplate::implementation
{
    struct FileItem : FileItemT<FileItem>
    {
        FileItem(winrt::xBindSampleModel::FileItem);

        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage ImageData();
        winrt::hstring DisplayName();
        winrt::hstring prettyDate();
        winrt::hstring prettyFileSize();
        winrt::hstring prettyImageSize();

    private:
        winrt::xBindSampleModel::IFileItemClass _item;
    };

    struct PhasingTests : PhasingTestsT<PhasingTests>
    {
        PhasingTests();
        ~PhasingTests();

        void Reset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ChangeFolderClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SlowPhasing_UnChecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SlowPhasing_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void PhasedTemplate_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        bool initialized {false};
        winrt::xBindSampleModel::DataModel _model;
        winrt::xBindSampleModel::FileDataSource _dataSource;
        event_token _CCToken, _CCCToken;

        void myGridView_ContainerContentChanging(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs const& args);
        void DataSource_VectorChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Foundation::Collections::IVectorChangedEventArgs const& e);

        // aux coroutines
        winrt::fire_and_forget CoroChangeFolderClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct PhasingTests : PhasingTestsT<PhasingTests, implementation::PhasingTests>
    {
    };

    struct FileItem : FileItemT<FileItem, implementation::FileItem>
    {
    };
}
