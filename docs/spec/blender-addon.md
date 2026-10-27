> 本ファイルは仕様書（正本）の一部である。設計書 版0.5 を章ごとに分割したもの。
> 仕様を変更する場合は、まずこのファイルの変更 PR を出し、承認後に実装 PR を出すこと。

## 7. Blender アドオン仕様

### 7.1 パネル項目

- ブラックホール: 質量（見た目のスケール）、スピン $a/M$（0〜0.998、初期値 0）
- 円盤: 内縁（ISCO 自動 / 手動）、外縁、厚み、温度スケール、密度、乱流の強さ、流れの時刻
- パーティクル: 数、大きさ、速度分散
- レンダー: 解像度、最大ステップ数、逃散半径、出力先
- カメラ／レンズ: ゲートプリセット（§6.9）、焦点距離、F値、レンズプリセット、フレアの強さ、前玉の汚れテクスチャ
- フィルム: ハレーション、グレイン、ゲートウィーブの ON/OFF と強さ
- ボタン: プレビュー / 本番 / 前回の結果をコンポジターに読み込む

### 7.2 書き出し形式（scene.json の例）

```json
{
  "camera": { "location": [60.0, -80.0, 25.0], "rotation_euler": [1.2, 0.0, 0.6], "fov_deg": 40.0 },
  "blackhole": { "mass": 1.0, "spin": 0.0 },
  "disk": { "r_in_mode": "isco", "r_out": 20.0, "thickness": 0.08,
            "temperature_scale": 1.0, "density": 1.0, "turbulence": 0.7, "flow_time": 0.0 },
  "particles": { "count": 100000, "size": 0.05, "velocity_dispersion": 0.02, "seed": 42 },
  "render": { "width": 1920, "height": 1080, "max_steps": 3000, "escape_radius": 200.0,
              "render_scale": 1.0, "overscan": 1.25 },
  "lens": { "preset": "cine65_50mm", "gate": "imax_15_70", "f_number": 2.8,
            "flare_strength": 1.0, "flare_scale": 0.5, "spectral_samples": 9, "front_dirt": "dirt.png" },
  "film": { "halation": 0.5, "grain": 0.3, "gate_weave": 0.0 },
  "sky": "sky.exr",
  "meshes": "scene.glb"
}
```

アドオンはこの JSON と glb を書き出し、外部レンダラーをサブプロセスで呼び、生成された EXR を Blender の画像として開くところまでを担う。それ以外の仕事はしない。

---

