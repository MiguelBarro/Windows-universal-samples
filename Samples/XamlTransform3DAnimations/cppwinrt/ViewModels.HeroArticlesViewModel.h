#pragma once
#include "ViewModels.HeroArticlesViewModel.g.h"

namespace winrt::Transform3DAnimations::ViewModels::implementation
{
    struct HeroArticlesViewModel : HeroArticlesViewModelT<HeroArticlesViewModel>
    {
        HeroArticlesViewModel() = default;

        Transform3DAnimations::ViewModels::ArticleViewModel Article0();
        void Article0(Transform3DAnimations::ViewModels::ArticleViewModel const& value);
        Transform3DAnimations::ViewModels::ArticleViewModel Article1();
        void Article1(Transform3DAnimations::ViewModels::ArticleViewModel const& value);
        event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(event_token const& token) noexcept;

    private:
        winrt::event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChanged;
        Transform3DAnimations::ViewModels::ArticleViewModel _a0, _a1;
    };
}
namespace winrt::Transform3DAnimations::ViewModels::factory_implementation
{
    struct HeroArticlesViewModel : HeroArticlesViewModelT<HeroArticlesViewModel, implementation::HeroArticlesViewModel>
    {
    };
}
