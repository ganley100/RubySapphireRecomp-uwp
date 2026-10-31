// Pure UWP launcher (CoreApplication + CoreWindow).
// Builds with CMAKE_SYSTEM_NAME=WindowsStore for Xbox / Windows sideload.

#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;
using namespace Windows::System;

struct AppView : implements<AppView, IFrameworkView>
{
    bool m_closed{ false };

    void Initialize(CoreApplicationView const&)
    {
    }

    void SetWindow(CoreWindow const& window)
    {
        window.Closed([this](auto&&, auto&&) { m_closed = true; });

        window.KeyDown([](auto&&, KeyEventArgs const& args) {
            auto key = args.VirtualKey();
            if (key == VirtualKey::Escape || key == VirtualKey::GamepadB) {
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

        while (!m_closed) {
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
    init_apartment(apartment_type::single_threaded);
    CoreApplication::Run(make<AppViewSource>());
    return 0;
}
