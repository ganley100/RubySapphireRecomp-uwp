# UWP Launcher (Xbox / Windows)

Minimal **UWP package** that installs on Xbox One / Series and Windows.
This is **only the launcher shell** — it does not yet embed the full Ruby/Sapphire recomp engine.

## What you get

- `Package.appxmanifest` — identity, Xbox + desktop capabilities
- Blank C++/WinRT-style entry (`App.cpp`) that shows a simple title screen
- Asset placeholders (replace with real logos before Store submission)
- Instructions to build & sideload with Visual Studio

## Requirements

- Visual Studio 2022
- Workloads:
  - **Desktop development with C++**
  - **Universal Windows Platform development**
  - (Optional) **Game development with C++** / Xbox development tools if targeting Xbox hardware
- Windows 10/11 SDK (10.0.19041.0 or newer)

## Build & deploy

### Option A — Visual Studio (recommended)

1. Open **Developer Command Prompt for VS 2022** or use the IDE.
2. Create a new **Blank App (C++/WinRT)** UWP project temporarily, or use the files under `uwp/` as the starting point.
3. Copy / add:
   - `Package.appxmanifest`
   - `App.cpp` / `App.h` / `pch.h` / `pch.cpp`
   - `Assets\*`
4. Set target to **x64** (Xbox and modern Windows).
5. Set deployment target:
   - Local Machine (Windows)
   - or **Remote Machine / Device** for Xbox (Developer Mode on)
6. Build → Deploy.

### Option B — Sideload MSIX on Xbox

1. Enable **Developer Mode** on the Xbox.
2. Build the package (Project → Publish → Create App Packages) as **sideload**.
3. Copy the `.msix` / `.msixbundle` to the console (USB or network).
4. Install via Xbox Device Portal or `Add-AppxPackage` from a connected PC.

## ROM / game binary

This launcher does **not** ship ROMs.
When you later wire the full recomp:

- User places `ruby_usa.gba` / `sapphire_usa.gba` in the app `LocalState` folder, **or**
- Launcher opens a file picker (UWP `FileOpenPicker`) and copies into `LocalState`.

Never commit ROMs to the repo.

## Next steps (after the shell works)

1. Confirm the blank launcher deploys on your Xbox / PC.
2. Add a simple UI: “Select Ruby ROM” / “Select Sapphire ROM”.
3. Link `gbarecomp` runtime under a UWP-compatible platform layer (Phase 2).
4. Package the recompiled game as a library loaded by this launcher.

## Identity (edit before publishing)

In `Package.appxmanifest`:

- `Name` / `Publisher` must match your certificate
- `PhoneIdentity` / Xbox product IDs only matter for Store submission
