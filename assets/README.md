# assets

レンズプリセット等のデータ置き場。大きなファイル (.exr, .hdr) は
Git LFS で管理する (.gitattributes 参照)。

- `lens_presets/`: レンズ処方データ (曲率半径、表面間距離、ガラスの
  屈折率/分散、口径、コーティング膜厚)。仕様は
  `docs/spec/renderer.md` のレンズシミュレーション節を参照
