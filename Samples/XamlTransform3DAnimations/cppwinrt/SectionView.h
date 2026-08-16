#pragma once
#include "SectionView.g.h"
#include "ViewModels.HeroArticlesViewModel.h"

namespace winrt::Transform3DAnimations::implementation
{
    struct SectionView : SectionViewT<SectionView>
    {
        SectionView();
        ~SectionView();

        static winrt::Windows::UI::Xaml::DependencyProperty ViewModelProperty();
        Transform3DAnimations::ViewModels::HeroArticlesViewModel ViewModel();
        void ViewModel(winrt::Transform3DAnimations::ViewModels::HeroArticlesViewModel const& value);
        event_token ArticleSelected(
                winrt::Windows::Foundation::TypedEventHandler<
                    Transform3DAnimations::SectionView,
                    Transform3DAnimations::ViewModels::ArticleViewModel> const& handler);
        void ArticleSelected(winrt::event_token const& token) noexcept;
        void LayoutRoot_SizeChanged(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);
        void ContentTransitionStoryboard_Completed(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::Foundation::IInspectable const& e);
        void ArticleTapped(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e);
        void OnViewModelChanged(
                ViewModels::HeroArticlesViewModel const& oldValue,
                ViewModels::HeroArticlesViewModel const& newValue);
        static void OnViewModelPropertyChanged(
                Windows::UI::Xaml::DependencyObject const& o,
                Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
    private:
        Windows::UI::ViewManagement::UISettings _uiSettings;
        event<
            Windows::Foundation::TypedEventHandler<
                    Transform3DAnimations::SectionView,
                    Transform3DAnimations::ViewModels::ArticleViewModel>> _event;
        event_token _token;

        void UpdateForSizeChanged(float newWidth, float newHeight);
    };
}
namespace winrt::Transform3DAnimations::factory_implementation
{
    struct SectionView : SectionViewT<SectionView, implementation::SectionView>
    {
    };
}
