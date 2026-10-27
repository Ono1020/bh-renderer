# bh-renderer

一般相対論に基づくブラックホール・レンダラー。

光の測地線を実際に積分し、ブラックホールの影・フォトンリング・
重力レンズで上下に回り込む降着円盤・ドップラービーミングを
物理的に計算して描く。仕上げには、実在レンズの処方データに
基づくレンズフレアとフィルム特性を重ね、「IMAX フィルムカメラで
現地で撮影してきたような映像」を目指す。

- 仕様書: [docs/spec/](docs/spec/)
- 構成: [docs/architecture.md](docs/architecture.md)
- 開発手順: [docs/development.md](docs/development.md)
- 進め方: [CONTRIBUTING.md](CONTRIBUTING.md)

## 構成

| 要素 | 実装 |
|---|---|
| シーン編集 | Blender (+ 専用アドオン `blender_addon/`) |
| レンダラー | C++20 + Vulkan Compute (`renderer/`) |
| リファレンス実装 | [BHraytracer](https://github.com/Ono1020/BHraytracer) (Phase 0 検証済み CPU 実装) |

## 状態

開発初期 (Phase 1: Vulkan Compute 最小レンダラーの構築中)。
ロードマップは `docs/spec/verification-and-roadmap.md` を参照。

## ライセンス

MIT
