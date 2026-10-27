# bh-renderer — Claude Code 向けガイド

## このプロジェクトは何か

一般相対論に基づくブラックホール・レンダラー。『インターステラー』の
ガルガンチュアのような像を、見た目の近似ではなく光の測地線を実際に
積分して描くことが目的。Blender はシーン編集専用、描画は別体の
Vulkan Compute レンダラーが行い、薄い Blender アドオンで接続する。

## 必読 (作業前に該当分だけ読むこと)

- 仕様の正本: `docs/spec/` (章ごとに分割。変更は仕様 PR を先に出す)
- 構成と データの流れ: `docs/architecture.md`
- 設計判断の記録: `docs/decisions/` (ADR)
- 開発手順: `docs/development.md`

## リポジトリ地図

| パス | 内容 |
|---|---|
| `renderer/` | C++20 + Vulkan Compute 本体 (CMake) |
| `renderer/shaders/` | GLSL Compute Shader |
| `renderer/include/bh/` | 物理量などのヘッダ |
| `blender_addon/` | Blender アドオン (Python) |
| `assets/` | レンズプリセット等のデータ |
| `examples/` | サンプル scene.json |
| `docs/spec/` | 仕様書 (正本) |

## ビルドとテスト

```sh
cmake -S renderer -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
python3 blender_addon/tests/test_addon_metadata.py
```

コミット前に必ずテストを実行すること。push 時は `.githooks/pre-push`
でも実行される (有効化: `git config core.hooksPath .githooks`)。

## 物理の不変条件 (最重要)

- 計量・測地線の方程式を変更する PR は、`docs/spec/physics.md` の
  変更と検証テストの追加・更新を必ず伴うこと
- 検証の物差しは BHraytracer (https://github.com/Ono1020/BHraytracer)
  の `tests/test_geodesic.cpp` にある期待値:
  曲がり角、影 b_crit = 3√3 M、フォトン球 r = 3M、保存量ドリフト
- 単位系は幾何単位系 G = c = 1、M = 1 を基本とする (spec 参照)

## 規約

- ブランチ: `feat/<issue>-<slug>`, `fix/`, `docs/`, `exp/`。main へ直接 push しない
- コミット: Conventional Commits (例: `feat(renderer): ...`)
- PR は小さく保つ (目安 400 行以内)。1 Issue = 1 ブランチ = 1 PR
- コメントとドキュメントは日本語、識別子は英語
- C++ は `.clang-format` に従う
