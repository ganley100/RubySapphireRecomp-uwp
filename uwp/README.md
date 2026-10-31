# UWP Launcher (Xbox / Windows) — shell only

Minimal **UWP package** that installs on Xbox One / Series and Windows.
This is **only the launcher shell** (dark window + gamepad Back/B to exit).
It does **not** embed the Ruby/Sapphire recomp engine yet.

## Files

| Path | Purpose |
|------|---------|
| `Package.appxmanifest` | App identity, Xbox + desktop families, gamepad capability |
| `App.cpp` | `CoreApplication` + `CoreWindow` entry (no XAML) |
| `pch.h` / `pch.cpp` | WinRT precompiled headers |
| `Assets/` | Tile / splash PNGs (add before packaging) |

## Fastest way to get it on a device

### 1. Create a VS project and point it at these sources

1. Visual Studio 2022 → **Create a new project**
2. Template: **Blank App (C++/WinRT)** → UWP  
   (or **DirectX 11 App (UWP)** if you prefer a game-style project)
3. Name it e.g. `RubySapphireLauncher`, platform **x64**
4. Replace the generated `App.cpp` / `pch.*` with the files from this `uwp/` folder
5. Replace `Package.appxmanifest` with the one here (fix Publisher `CN=...` to match your cert)
6. Project properties → **C/C++** → **Language** → **C++ Language Standard** = `/std:c++17` or later
7. Add WinRT projection references if the Blank template didn’t already (Windows SDK)

### 2. Assets

Use **Project → Add → New Item → UWP → Asset Generator**, or drop PNGs into `Assets/`  
(see `Assets/README.md` for sizes).

### 3. Deploy

- **Windows:** set target to Local Machine → F5  
- **Xbox:** enable Developer Mode on the console → Remote Machine / Device Portal → Deploy  
  Or **Publish → Create App Packages** (sideload) and install the `.msix` via Device Portal

## Controls (shell)

- **B / Escape** — exit the launcher

## ROM policy

No ROMs in the package. When the full game is wired later:

- User picks a ROM with `FileOpenPicker`, or
- Copies into `ApplicationData.Current().LocalFolder()`

## Publisher / identity

Edit before real distribution:

```xml
<Identity Name="ganley100.RubySapphireRecomp"
          Publisher="CN=ganley100"
          Version="0.1.0.0" />
```

`Publisher` must match the certificate you sign with (VS creates a test cert automatically for sideload).

## What’s next

1. Confirm this shell deploys on your Xbox / PC  
2. Add a simple “Select ROM” button / gamepad menu  
3. Link `gbarecomp` under a UWP-safe platform layer  
