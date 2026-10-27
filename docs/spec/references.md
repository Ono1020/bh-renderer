> 本ファイルは仕様書（正本）の一部である。設計書 版0.5 を章ごとに分割したもの。
> 仕様を変更する場合は、まずこのファイルの変更 PR を出し、承認後に実装 PR を出すこと。

## 11. 参考文献・参考実装

1. James, O. et al. (2015). "Gravitational lensing by spinning black holes in astrophysics, and in the movie Interstellar." *Classical and Quantum Gravity* 32, 065001. — DNEG のレンダラー DNGR の論文。本プロジェクトの直接の手本
2. Thorne, K. (2014). *The Science of Interstellar*. — ガルガンチュアのパラメータ（スピン、円盤）の出典
3. Luminet, J.-P. (1979). "Image of a spherical black hole with thin accretion disk." *Astronomy and Astrophysics* 75, 228. — 手計算に近い方法で描かれた最初のブラックホールの像。今でも検証の基準になる
4. Bardeen, J. M., Press, W. H., Teukolsky, S. A. (1972). "Rotating black holes: locally nonrotating frames, and general relativistic magnetohydrodynamics." *ApJ* 178, 347. — ISCO の式の出典
5. Shakura, N. I., Sunyaev, R. A. (1973). 標準降着円盤モデルの原論文。§4.3 の温度分布の出典
6. GYOTO（汎用相対論レイトレーシングコード）、ipole（EHT 向け偏光放射輸送） — 将来の発展形の参考
7. CAPCOM (2023). "Ray Tracing Lens Flare." CAPCOM オープンカンファレンス プロフェッショナル RE:2023. https://www.docswell.com/s/CAPCOM_RandD/KYWLRL-RE2023/1 — §6.7 の直接の手本。レンズ内光線追跡によるゴースト、薄膜干渉による着色、Fraunhofer 回折によるスターバースト、帯域制限角スペクトル法、前玉のゴミの反映
8. Hullin, M. et al. (2011). "Physically-based real-time lens flare rendering." *ACM Trans. Graph.* 30(4). — CAPCOM 手法の元論文
9. Matsushima, K., Shimobaba, T. (2009). "Band-Limited Angular Spectrum Method..." *Opt. Express* 17(22). — ゴースト像の回折伝搬

---


## 付録 A: 記号表

| 記号 | 意味 |
|---|---|
| $M$ | ブラックホールの質量（= 1 に規格化） |
| $a$ | スピンパラメータ。$a/M$ が無次元の回転の大きさ |
| $r_+$ | 事象の地平面。$r_+ = M + \sqrt{M^2 - a^2}$ |
| $r_{ISCO}$ | 最内安定円軌道。円盤内縁の基準 |
| $p_\mu$ | 光子（または粒子）の4元運動量 |
| $\lambda$ | アフィンパラメータ（光線の進み具合） |
| $g$ | 赤方偏移係数 $\nu_{obs}/\nu_{emit}$（ドップラーと重力の合算） |
| $\Omega(r)$ | 円軌道の角速度 |
| $b$ | インパクトパラメータ |


## 付録 B: 未決事項

1. ホスト言語は C++ で確定としてよいか（Rust + ash という選択肢もあるが、資料の多さで C++ を推奨）
2. 星空テクスチャは実在の星図（例: Gaia / Tycho の天球画像）を使うか、人工生成にするか。前者の方がレンズ像の歪みが分かりやすく、検証にも使えるので推奨は実在の星図
3. 動画対応を Phase 3 で入れるか、静止画完成後に回すか（設計上は時刻パラメータを持たせてあるので、後回しでも手戻りはない）
