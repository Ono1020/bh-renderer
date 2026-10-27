// bh-renderer エントリポイント (Phase 1 スキャフォールド)
// 現段階では基礎量の表示のみ。パイプライン構成は docs/spec/renderer.md。
#include <bh/physics.hpp>

#include <cstdio>

int main() {
  const double mass = 1.0;
  std::printf("bh-renderer 0.1.0 (scaffold)\n");
  std::printf("M = %.1f (geometric units, G = c = 1)\n", mass);
  std::printf("  horizon r+      = %.4f\n", bh::schwarzschildRadius(mass));
  std::printf("  photon sphere   = %.4f\n", bh::photonSphereRadius(mass));
  std::printf("  ISCO            = %.4f\n", bh::iscoRadiusSchwarzschild(mass));
  std::printf("  b_crit (shadow) = %.4f\n", bh::criticalImpactParameter(mass));
  return 0;
}
