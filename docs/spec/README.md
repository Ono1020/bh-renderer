# 仕様書 (正本)

このディレクトリが仕様の正本である。実装はここに書かれた内容に従い、
仕様を変える場合は実装より先にここの変更 PR を出す。

| ファイル | 内容 (設計書の章) |
|---|---|
| [overview.md](overview.md) | 0. 目的と設計判断 / 1. 全体アーキテクチャ / 2. 単位系と座標系 |
| [physics.md](physics.md) | 3. 物理コア: 光の測地線 (Kerr 計量、ハミルトン形式、検証値) |
| [disk-and-particles.md](disk-and-particles.md) | 4. 降着円盤 (含むジェット、潮汐ストリーム) / 5. パーティクル |
| [renderer.md](renderer.md) | 6. レンダラー実装 (Vulkan Compute、レンズフレア、フィルム特性、解像度) |
| [blender-addon.md](blender-addon.md) | 7. Blender アドオン仕様 |
| [verification-and-roadmap.md](verification-and-roadmap.md) | 8. 検証計画 / 9. ロードマップ / 10. リスク |
| [references.md](references.md) | 11. 参考文献 / 付録 (記号表、未決事項) |

元の設計書 (版 0.5) を章ごとに分割したもの。設計判断の経緯は
`docs/decisions/` の ADR を参照。
