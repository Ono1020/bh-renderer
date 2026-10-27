# 開発手順

## 前提ツール

- CMake 3.20+ / C++20 対応コンパイラ
- Vulkan SDK (ヘッダとローダ)。シェーダ検証に glslangValidator
- clang-format (CI と同じ書式チェック)
- Python 3.10+ (アドオンのテスト用)
- Blender 4.x (アドオンの動作確認用。単体テストには不要)

## セットアップ

```sh
git clone https://github.com/Ono1020/bh-renderer.git
cd bh-renderer
git config core.hooksPath .githooks   # push 時にテストを自動実行
```

## ビルドとテスト

```sh
cmake -S renderer -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
python3 blender_addon/tests/test_addon_metadata.py
```

Vulkan が見つからない環境では、Vulkan を使う実行部は無効化され、
物理ヘッダとテストだけがビルドされる (CI の検証用)。

## シェーダ

```sh
glslangValidator -V renderer/shaders/geodesic.comp -o /tmp/geodesic.spv
```

## 書式

```sh
clang-format -i renderer/src/*.cpp renderer/include/bh/*.hpp renderer/tests/*.cpp
```

## 規約

- コメントとドキュメントは日本語、識別子は英語
- 作業の進め方は `CONTRIBUTING.md`、AI 向けの要点は `CLAUDE.md`
