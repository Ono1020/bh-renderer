> 本ファイルは仕様書（正本）の一部である。設計書 版0.5 を章ごとに分割したもの。
> 仕様を変更する場合は、まずこのファイルの変更 PR を出し、承認後に実装 PR を出すこと。

## 3. 物理コア: 光の測地線

### 3.1 計量

Kerr 計量（Boyer–Lindquist 座標、$G=c=1$）:

$$
\Sigma = r^2 + a^2 \cos^2\theta, \qquad \Delta = r^2 - 2Mr + a^2
$$

$$
ds^2 = -\left(1 - \frac{2Mr}{\Sigma}\right) dt^2
- \frac{4Mar\sin^2\theta}{\Sigma}\, dt\, d\phi
+ \frac{\Sigma}{\Delta} dr^2 + \Sigma\, d\theta^2
+ \left(r^2 + a^2 + \frac{2Ma^2 r \sin^2\theta}{\Sigma}\right) \sin^2\theta\, d\phi^2
$$

$a$ はスピンパラメータ（$0 \le a \le M$）。$a = 0$ と置けば Schwarzschild 計量

$$
ds^2 = -\left(1 - \frac{2M}{r}\right) dt^2 + \left(1 - \frac{2M}{r}\right)^{-1} dr^2 + r^2 d\theta^2 + r^2 \sin^2\theta\, d\phi^2
$$

に帰着する。**実装は最初から Kerr の形で書き、$a=0$ でテストする**のが二度手間にならない。

### 3.2 積分する方程式: ハミルトン形式

光子の運動は、共役運動量 $p_\mu$ を使ったハミルトン形式が数値的に安定で、Kerr でもそのまま使える。

$$
H = \frac{1}{2} g^{\mu\nu} p_\mu p_\nu = 0 \quad (\text{光子}), \qquad
\frac{dx^\mu}{d\lambda} = \frac{\partial H}{\partial p_\mu}, \qquad
\frac{dp_\mu}{d\lambda} = -\frac{\partial H}{\partial x^\mu}
$$

$\lambda$ はアフィンパラメータ。状態ベクトルは8次元: $(t, r, \theta, \phi, p_t, p_r, p_\theta, p_\phi)$。

この形式の利点:

- $p_t = -E$（エネルギー）と $p_\phi = L$（角運動量）が保存量として自動的に出る。積分の誤差チェックに使える
- Kerr では第3の保存量としてカーター定数 $Q$ があり、これも誤差チェックに使える
- 時間発展粒子（§5）も $H = -1/2$ に変えるだけで同じ積分器が使える

逆計量の非ゼロ成分（実装時にそのまま使う）:

$$
g^{tt} = -\frac{(r^2+a^2)^2 - a^2\Delta\sin^2\theta}{\Sigma\Delta}, \quad
g^{t\phi} = -\frac{2Mar}{\Sigma\Delta}, \quad
g^{rr} = \frac{\Delta}{\Sigma}, \quad
g^{\theta\theta} = \frac{1}{\Sigma}
$$
$$
g^{\phi\phi} = \frac{\Delta - a^2\sin^2\theta}{\Sigma\Delta\sin^2\theta}, \quad
g^{tr}=g^{t\theta}=\dots=0
$$

$\partial H / \partial x^\mu$ は解析的に書くのが速いが、式が長くバグの温床になる。
**Phase 1 では数値微分（中心差分）でよい。** オフライン前提なので速度より正確さと実装の確実さを優先し、プロファイルを見てから解析微分に差し替える。

### 3.3 初期条件: カメラから逆向きに撃つ

1. ピクセル位置から、カメラの向き・画角で直交座標の方向ベクトルを作る
2. カメラ位置を $(r, \theta, \phi)$ に変換し、方向ベクトルから $p_\mu$ の初期値を作る（カメラの4元速度との内積で規格化する）
3. 時間反転して積分する。つまり「光子がカメラに届いた経路」を過去向きに辿る

カメラがブラックホールから十分遠い（$r_{cam} \gtrsim 50M$）間は、カメラ付近の時空は平坦とみなしてよい。

### 3.4 積分器とステップ幅

- 積分器: 古典的4次 Runge–Kutta（RK4）。まずこれで十分。誤差が問題になったら適応型（RKF45）に上げる
- ステップ幅は適応させる。固定ステップは効率が悪すぎる
  - 目安: $\Delta\lambda \propto$（地平面までの距離、円盤面までの距離、$r$ 自体）
  - 遠方では大きく（$\sim r/5$）、フォトン球付近では小さく（$\sim 0.01M$）
- 終了条件:
  - $r < r_+ + \epsilon$（地平面に落下）→ そのピクセルは黒。ただし円盤の発光が手前にあればそれが残る
  - $r > r_{escape}$（例: $200M$）→ 到達方向で天球テクスチャを引く
  - ステップ数上限（例: 5000）に到達 → 黒として打ち切る（フォトン球周りを回り続ける光子への対策）

### 3.5 Schwarzschild で先に検証できる「正解」

Phase 0/1 の合格条件として使う。ここが合わないコードは Kerr に進んでも絶対に合わない。

| 検証項目 | 理論値 |
|---|---|
| 弱い場での光の曲がり角 | $\delta \approx 4M / b$（$b$ が大きいとき） |
| 影の大きさ | インパクトパラメータ $b_{crit} = 3\sqrt{3}M \approx 5.196M$ より内側から来る光は届かない |
| フォトン球 | $r = 3M$ に置いた光子は（不安定に）周回し続ける |
| 静止した放射源の重力赤方偏移 | $g = \sqrt{1 - 2M/r}$ |
| 保存量ドリフト | 長時間積分でも $E, L$ の相対変化が $10^{-6}$ 程度以下 |

---

