// 物理量の基礎定義 (幾何単位系 G = c = 1)
// 仕様の正本は docs/spec/physics.md。ここの値は検証テストと対応する。
#pragma once

#include <cmath>

namespace bh {

// 事象の地平面の半径 (Schwarzschild)
inline double schwarzschildRadius(double mass) { return 2.0 * mass; }

// フォトン球の半径 (Schwarzschild)
inline double photonSphereRadius(double mass) { return 3.0 * mass; }

// 最内安定円軌道 ISCO (Schwarzschild)
inline double iscoRadiusSchwarzschild(double mass) { return 6.0 * mass; }

// 影の臨界インパクトパラメータ b_crit = 3√3 M
inline double criticalImpactParameter(double mass) {
  return 3.0 * std::sqrt(3.0) * mass;
}

// 事象の地平面の半径 (Kerr)。a はスピンパラメータ (0 <= a <= M)
inline double horizonRadiusKerr(double mass, double spin) {
  return mass + std::sqrt(mass * mass - spin * spin);
}

// 円軌道の角速度 (Kerr、順行)。Schwarzschild では √(M/r³) に帰着する
inline double keplerOmega(double r, double mass, double spin) {
  return std::sqrt(mass) / (std::pow(r, 1.5) + spin * std::sqrt(mass));
}

} // namespace bh
