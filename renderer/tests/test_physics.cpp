// physics.hpp の基礎量が解析値と一致することの検証。
// 本格的な測地線の検証値は BHraytracer の tests/test_geodesic.cpp が正本。
#include <bh/physics.hpp>

#include <cmath>
#include <cstdio>

namespace {
int failures = 0;
void expectNear(const char *name, double got, double want, double tol) {
  bool ok = std::abs(got - want) < tol;
  std::printf("[%s] %s: got=%.10f want=%.10f\n", ok ? "PASS" : "FAIL", name, got, want);
  if (!ok)
    failures++;
}
} // namespace

int main() {
  const double m = 1.0;
  expectNear("schwarzschildRadius", bh::schwarzschildRadius(m), 2.0, 1e-12);
  expectNear("photonSphereRadius", bh::photonSphereRadius(m), 3.0, 1e-12);
  expectNear("iscoRadiusSchwarzschild", bh::iscoRadiusSchwarzschild(m), 6.0, 1e-12);
  expectNear("criticalImpactParameter", bh::criticalImpactParameter(m), 3.0 * std::sqrt(3.0),
             1e-12);
  expectNear("horizonRadiusKerr a=0", bh::horizonRadiusKerr(m, 0.0), 2.0, 1e-12);
  expectNear("horizonRadiusKerr a=M", bh::horizonRadiusKerr(m, m), 1.0, 1e-12);
  expectNear("keplerOmega ISCO", bh::keplerOmega(6.0, m, 0.0), std::sqrt(1.0 / 216.0), 1e-12);
  std::printf("%s (%d failure(s))\n", failures == 0 ? "ALL TESTS PASSED" : "TESTS FAILED",
              failures);
  return failures == 0 ? 0 : 1;
}
