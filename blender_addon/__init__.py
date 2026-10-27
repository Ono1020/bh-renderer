# bh-renderer Blender アドオン (Phase 4 スキャフォールド)
# 仕様は docs/spec/blender-addon.md。本実装は Phase 4 の Issue で行う。
bl_info = {
    "name": "BH Renderer",
    "author": "Ono1020",
    "version": (0, 1, 0),
    "blender": (4, 0, 0),
    "location": "View3D > Sidebar > BH Renderer",
    "description": "Export scene parameters and render with the external bh-renderer",
    "category": "Render",
}

try:
    import bpy  # noqa: F401

    _HAS_BPY = True
except ImportError:  # Blender 外 (テスト等) では登録処理を行わない
    _HAS_BPY = False


def register():
    if not _HAS_BPY:
        return
    # TODO(Phase 4): パネルとオペレータの登録


def unregister():
    if not _HAS_BPY:
        return
    # TODO(Phase 4): 登録解除
