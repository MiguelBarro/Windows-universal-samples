#pragma once
#include "ViewModels.ArticleViewModel.g.h"

namespace winrt::Transform3DAnimations::ViewModels::implementation
{
    struct ArticleViewModel : ArticleViewModelT<ArticleViewModel>
    {
        ArticleViewModel();

        hstring Headline();
        void Headline(hstring const& value);
        winrt::Windows::UI::Xaml::Media::ImageSource ImageSource();
        hstring FullText();

    private:
        std::mt19937 _gen;
        std::uniform_int_distribution<uint32_t> _random;
        hstring _headline;
        Windows::Foundation::Uri _imageUri { nullptr };
    };
}
namespace winrt::Transform3DAnimations::ViewModels::factory_implementation
{
    struct ArticleViewModel : ArticleViewModelT<ArticleViewModel, implementation::ArticleViewModel>
    {
    };
}
