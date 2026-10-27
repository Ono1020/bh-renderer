"""Blender 本体なしで実行できるアドオンのメタデータ検証。

使い方: python3 blender_addon/tests/test_addon_metadata.py
"""
import ast
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
INIT = ROOT / "blender_addon" / "__init__.py"


def main() -> int:
    tree = ast.parse(INIT.read_text(encoding="utf-8"))
    bl_info = None
    for node in tree.body:
        if isinstance(node, ast.Assign) and node.targets[0].id == "bl_info":
            bl_info = ast.literal_eval(node.value)
    assert bl_info is not None, "bl_info が見つからない"
    for key in ("name", "version", "blender", "category"):
        assert key in bl_info, f"bl_info に {key} がない"
    # Blender の構文として import できること (bpy は無い環境を想定)
    sys.path.insert(0, str(ROOT / "blender_addon"))
    import importlib.util

    spec = importlib.util.spec_from_file_location("bh_addon", INIT)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    module.register()  # bpy が無ければ何もしないことを確認
    module.unregister()
    print("PASS: addon metadata and import")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
