#include "pch.h"
#include "SectionView.h"
#include "SectionView.g.cpp"

namespace winrt::Transform3DAnimations::implementation
{
    SectionView::SectionView()
    {
        InitializeComponent();

        Windows::UI::Xaml::VisualStateManager::GoToState(
                get_strong().as<winrt::Windows::UI::Xaml::Controls::UserControl>(),
                L"ContentSteadyState", false);
    }

    SectionView::~SectionView()
    {
        if (_token)
            ArticleSelected(_token);
    }

    /*static*/
    winrt::Windows::UI::Xaml::DependencyProperty SectionView::ViewModelProperty_ =
            winrt::Windows::UI::Xaml::DependencyProperty::Register(
                    L"ViewModel",
                    winrt::xaml_typename<Transform3DAnimations::ViewModels::HeroArticlesViewModel>(),
                    winrt::xaml_typename<Transform3DAnimations::SectionView>(),
                    winrt::Windows::UI::Xaml::PropertyMetadata{nullptr, {&SectionView::OnViewModelPropertyChanged}});

    /*static*/
    winrt::Windows::UI::Xaml::DependencyProperty SectionView::ViewModelProperty()
    {
        return ViewModelProperty_;
    }

    winrt::Transform3DAnimations::ViewModels::HeroArticlesViewModel SectionView::ViewModel()
    {
        return GetValue(ViewModelProperty_).as<Transform3DAnimations::ViewModels::HeroArticlesViewModel>();
    }

    void SectionView::ViewModel(winrt::Transform3DAnimations::ViewModels::HeroArticlesViewModel const& value)
    {
        SetValue(ViewModelProperty_, winrt::box_value(value));
    }

    winrt::event_token SectionView::ArticleSelected(
            winrt::Windows::Foundation::TypedEventHandler<
                Transform3DAnimations::SectionView,
                Transform3DAnimations::ViewModels::ArticleViewModel> const& handler)
    {
        return _event.add(handler);
    }

    void SectionView::ArticleSelected(winrt::event_token const& token) noexcept
    {
        _event.remove(token);
    }

    void SectionView::LayoutRoot_SizeChanged(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
    {
        auto newSize = e.NewSize();
        UpdateForSizeChanged(newSize.Width, newSize.Height);
    }

    void SectionView::ContentTransitionStoryboard_Completed(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::Foundation::IInspectable const&)
    {
        CurrentContentPresenter().Content(NextContentPresenter().Content());
        Windows::UI::Xaml::VisualStateManager().GoToState(
                get_strong().as<winrt::Windows::UI::Xaml::Controls::UserControl>(),
                L"ContentSteadyState", false);
    }

    void SectionView::ArticleTapped(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e)
    {
        if (_event)
            _event(
                *this,
                e.OriginalSource().as<winrt::Windows::UI::Xaml::FrameworkElement>()
                    .DataContext().as<Transform3DAnimations::ViewModels::ArticleViewModel>());
    }

    void SectionView::OnViewModelChanged(
            ViewModels::HeroArticlesViewModel const& oldValue,
            ViewModels::HeroArticlesViewModel const& newValue)
    {
        if (oldValue && _uiSettings.AnimationsEnabled())
        {
            NextContentPresenter().Content(newValue);
            CurrentContentPresenter().Content(oldValue);

            // Play content transition
            Windows::UI::Xaml::VisualStateManager::GoToState(
                    get_strong().as<winrt::Windows::UI::Xaml::Controls::UserControl>(),
                    L"ContentTransitionState", true);
        }
        else
        {
            CurrentContentPresenter().Content(newValue);
        }
    }

    void SectionView::UpdateForSizeChanged(float newWidth, float newHeight)
    {
        // The rotation creates a rectangular prism effect.
        // The center of rotation should be at X = Width / 2 and Z = -Width / 2
        auto centerX = newWidth / 2.0f;
        RootTransform().CenterX(centerX);
        NextContentTransform().CenterX(centerX);

        auto centerZ = -newWidth / 2.0f;
        RootTransform().CenterZ(centerZ);
        NextContentTransform().CenterZ(centerZ);

        // Clip to our left and right bounds so the effect doesn't get too crazy.
        ClipGeometry().Rect(Windows::Foundation::Rect(0.0f, -1024.0f, newWidth, newHeight + 1024.0f));
    }

    /*static*/
    void SectionView::OnViewModelPropertyChanged(
            Windows::UI::Xaml::DependencyObject const& o,
            Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        o.as<Transform3DAnimations::SectionView>().OnViewModelChanged(
                e.OldValue().as<Transform3DAnimations::ViewModels::HeroArticlesViewModel>(),
                e.NewValue().as<Transform3DAnimations::ViewModels::HeroArticlesViewModel>());
    }
}
