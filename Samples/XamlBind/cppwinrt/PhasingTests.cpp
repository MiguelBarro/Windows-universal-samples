#include "pch.h"
#include "PhasingTests.h"
#include "PhasingTests.g.cpp"

#include "winrt/Windows.Foundation.Collections.h"

#include "winrt/xBindSampleModel.h"

namespace winrt::SDKTemplate::implementation
{
    PhasingTests::PhasingTests()
    {
        // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#rcoro-capture
        [](PhasingTests& self) -> winrt::fire_and_forget
        {
            auto lifetime = self.get_strong();

            co_await self._dataSource.SetupDataSourceUsingPicturesFolder();

            self._CCToken = self._dataSource.try_as<winrt::xBindSampleModel::IFileDataSourceClass>()
                .VectorChanged({ &self, &PhasingTests::DataSource_VectorChanged });

            self.LoadingPanel().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
            self.myGridView().ItemsSource(self._dataSource);
            self.initialized = true;
        }(*this);
    }

    PhasingTests::~PhasingTests()
    {
        if (_CCToken)
            _dataSource.CollectionChanged(_CCToken);

        if (_CCCToken)
            myGridView().ContainerContentChanging(_CCCToken);
    }

    void PhasingTests::Reset_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _dataSource.ResetCollection();
    }

    void PhasingTests::ChangeFolderClick(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        CoroChangeFolderClick(sender, e);
    }

    winrt::fire_and_forget
    PhasingTests::CoroChangeFolderClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto lifetime = get_strong();

        winrt::Windows::Storage::Pickers::FolderPicker picker;
        picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::PicturesLibrary);
        picker.FileTypeFilter().Append(L".jpg");
        picker.FileTypeFilter().Append(L".png");

        winrt::Windows::Storage::StorageFolder f = co_await picker.PickSingleFolderAsync();
        if (f)
        {
            _dataSource.try_as<winrt::xBindSampleModel::IFileDataSourceClass>().VectorChanged(_CCToken);
            _dataSource = winrt::xBindSampleModel::FileDataSource();
            _CCToken = _dataSource.try_as<winrt::xBindSampleModel::IFileDataSourceClass>()
                .VectorChanged({ this, &PhasingTests::DataSource_VectorChanged });
            myGridView().ItemsSource(_dataSource);
            LoadingPanel().Visibility(Windows::UI::Xaml::Visibility::Visible);
            co_await _dataSource.SetupDataSource(f);
            LoadingPanel().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
        }
    }

    void PhasingTests::SlowPhasing_UnChecked(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SlowPhasing_Checked(sender, e);
    }

    void PhasingTests::SlowPhasing_Checked(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        if (initialized)
        {
            if (SlowPhasing().IsChecked().Value())
            {
                _CCCToken = myGridView().ContainerContentChanging({ this, &PhasingTests::myGridView_ContainerContentChanging });
            }
            else
            {
                myGridView().ContainerContentChanging(_CCCToken);
            }
        }
    }

    void PhasingTests::PhasedTemplate_Checked(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        if (initialized)
        {
            if (RadioPhasedTempl().IsChecked().Value())
            {
                myGridView().ItemTemplate(Resources().Lookup(box_value(L"PhasedFileTemplate"))
                        .as<winrt::Windows::UI::Xaml::DataTemplate>());
            }
            else if (RadioxBindTempl().IsChecked().Value())
            {
                myGridView().ItemTemplate(Resources().Lookup(box_value(L"NonPhasedFileTemplate"))
                        .as<winrt::Windows::UI::Xaml::DataTemplate>());
            }
            else if (RadioClassicTempl().IsChecked().Value())
            {
                myGridView().ItemTemplate(Resources().Lookup(box_value(L"ClassicBindingFileTemplate"))
                        .as<winrt::Windows::UI::Xaml::DataTemplate>());
            }
        }
    }

    void PhasingTests::myGridView_ContainerContentChanging(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs const& args)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (args.Phase() < 10)
            args.RegisterUpdateCallback({ this, &PhasingTests::myGridView_ContainerContentChanging });
    }

    void PhasingTests::DataSource_VectorChanged(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::Foundation::Collections::IVectorChangedEventArgs const&)
    {
        NoItemsPanel().Visibility(_dataSource.Count() == 0
                ?  winrt::Windows::UI::Xaml::Visibility::Visible
                : winrt::Windows::UI::Xaml::Visibility::Collapsed);
    }
}
