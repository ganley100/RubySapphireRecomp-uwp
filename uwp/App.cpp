// Minimal UWP / Xbox launcher using CoreApplication + CoreWindow.
// No XAML required — suitable as a game-style entry point.
//
// Build with a Visual Studio "Windows Application Packaging Project" or a
// Blank App (C++/WinRT) that you retarget to this CoreApplication path.
//
// This shell only draws a solid background and title text placeholder.
// Later: file picker for ROM, then load the recomp runtime.

#include "pch.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;
using namespace Windows::UI::ViewManagement;
using namespace Windows::System;

struct AppView : implements<AppView, IFrameworkView>
{
    Composition::Compositor m_compositor{ nullptr };
    Composition::ContainerVisual m_root{ nullptr };
    Composition::SpriteVisual m_bg{ nullptr };
    bool m_windowClosed{ false };

    void Initialize(CoreApplicationView const&)
    {
    }

    void SetWindow(CoreWindow const& window)
    {
        window.Activate();

        window.Closed([this](auto&&, auto&&) {
            m_windowClosed = true;
        });

        // Preferred launch size on desktop; Xbox ignores this.
        ApplicationView::GetForCurrentView().SetPreferredMinSize(
            Windows::Foundation::Size{ 1280, 720 });

        m_compositor = Composition::Compositor{};
        m_root = m_compositor.CreateContainerVisual();

        auto target = m_compositor.CreateTargetForCurrentView();
        target.Root(m_root);

        m_bg = m_compositor.CreateSpriteVisual();
        m_bg.Brush(m_compositor.CreateColorBrush(
            Windows::UI::ColorHelper::FromArgb(255, 26, 26, 46))); // #1a1a2e
        m_bg.Size({ static_cast<float>(window.Bounds().Width),
                    static_cast<float>(window.Bounds().Height) });
        m_root.Children().InsertAtTop(m_bg);

        window.SizeChanged([this](CoreWindow const& w, auto&&) {
            if (m_bg) {
                m_bg.Size({ static_cast<float>(w.Bounds().Width),
                            static_cast<float>(w.Bounds().Height) });
            }
        });

        // Gamepad: Back / B can exit the launcher shell for now.
        window.KeyDown([this](CoreWindow const&, KeyEventArgs const& args) {
            if (args.VirtualKey() == VirtualKey::Escape ||
                args.VirtualKey() == VirtualKey::GamepadB) {
                CoreApplication::Exit();
            }
        });
    }

    void Load(hstring const&)
    {
    }

    void Run()
    {
        auto window = CoreWindow::GetForCurrentThread();
        window.Activate();

        while (!m_windowClosed) {
            window.Dispatcher().ProcessEvents(
                CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }

    void Uninitialize()
    {
    }
};

struct AppViewSource : implements<AppViewSource, IFrameworkViewSource>
{
    IFrameworkView CreateView()
    {
        return make<AppView>();
    }
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    CoreApplication::Run(make<AppViewSource>());
    return 0;
}
