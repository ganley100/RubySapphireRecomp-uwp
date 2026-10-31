#!/usr/bin/env python3
"""Generate UWP tile/splash assets from boxart.b64 (Pokemon Ruby cover)."""
import base64, sys, io
from pathlib import Path

def main(data_file: Path, out_dir: Path):
    try:
        from PIL import Image
    except ImportError:
        import subprocess
        subprocess.check_call([sys.executable, "-m", "pip", "install", "pillow", "-q"])
        from PIL import Image

    raw = base64.b64decode(data_file.read_text().strip())
    src = Image.open(io.BytesIO(raw)).convert("RGBA")
    out_dir.mkdir(parents=True, exist_ok=True)

    def square(size):
        w, h = src.size
        side = min(w, h)
        left, top = (w - side) // 2, (h - side) // 2
        return src.crop((left, top, left + side, top + side)).resize((size, size), Image.Resampling.LANCZOS)

    def cover(size):
        tw, th = size
        sw, sh = src.size
        scale = max(tw / sw, th / sh)
        nw, nh = int(sw * scale), int(sh * scale)
        resized = src.resize((nw, nh), Image.Resampling.LANCZOS)
        left, top = (nw - tw) // 2, (nh - th) // 2
        return resized.crop((left, top, left + tw, top + th))

    assets = {
        "StoreLogo.png": square(50),
        "Square44x44Logo.png": square(44),
        "Square71x71Logo.png": square(71),
        "Square150x150Logo.png": square(150),
        "Wide310x150Logo.png": cover((310, 150)),
        "SplashScreen.png": cover((620, 300)),
    }
    for name, im in assets.items():
        im.save(out_dir / name, "PNG")
        print("wrote", name, im.size)

if __name__ == "__main__":
    root = Path(__file__).resolve().parent
    data = Path(sys.argv[1]) if len(sys.argv) > 1 else root / "boxart.b64"
    out = Path(sys.argv[2]) if len(sys.argv) > 2 else root / "Assets"
    main(data, out)
