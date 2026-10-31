#pragma once

#include "pch.h"

namespace winrt::RubySapphireRecomp::implementation
{
    struct App : winrt::implements<App, winrt::Windows::UI::Xaml::Markup::IXamlMetadataProvider>
    {
        App();
        void OnLaunched(winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e);

        // Minimal IXamlMetadataProvider stub (no XAML types yet)
        winrt::Windows::UI::Xaml::Markup::IXamlType GetXamlType(winrt::Windows::UI::Xaml::Interop::TypeName const& type);
        winrt::Windows::UI::Xaml::Markup::IXamlType GetXamlType(winrt::hstring const& fullName);
        winrt::com_array<winrt::Windows::UI::Xaml::Markup::XmlnsDefinition> GetXmlnsDefinitions();
    };
}
