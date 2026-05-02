---
name: zmk-firmware
description: Guides ZMK keyboard firmware using development (main) docs and blog. Always treats ZMK Studio as a core feature alongside build/flash. Use when working in this repo on ZMK firmware, user config, Devicetree keymaps, Zephyr/West, split/BLE, ZMK Studio, or ZMK keycodes.
---

# ZMK Firmware (this repo)

## Documentation version

1. **Use the development documentation** at [zmk.dev/docs](https://zmk.dev/docs) — this tracks `main` and matches active upstream work. **Do not** default to the v0.3 release snapshot ([v0-3-branch docs](https://v0-3-branch.zmk.dev/docs/)) unless the user explicitly asks for that release.
2. **Blog**: [zmk.dev/blog](https://zmk.dev/blog) for Zephyr bumps, breaking changes, Studio updates, and pinning advice.
3. **Never invent keycodes or Devicetree nodes.** Prefer [Keymaps](https://zmk.dev/docs/keymaps), [Behaviors](https://zmk.dev/docs/keymaps/behaviors), and [List of keycodes](https://zmk.dev/docs/keymaps/list-of-keycodes).

## ZMK Studio (always include)

**ZMK Studio** is a first-class part of the workflow for this project: [Realtime Keymap Updating / Studio](https://zmk.dev/docs/features/studio). Whenever you describe features, workflows, or “how to change the keymap,” include Studio alongside traditional edit → build → flash (browser or desktop app per current docs). Note Studio’s documented requirements and limitations (still marked 🚧 in the intro feature table where applicable) from the development docs, not from memory.

## What to emphasize

- User config, `west`, board/shield: [Getting Started](https://zmk.dev/docs/category/getting-started) / [Customizing ZMK](https://zmk.dev/docs/customizing-zmk).
- **Studio + static keymaps**: changing behavior at runtime vs in Devicetree; point to Studio docs for connection, unlocking, and supported operations.
- Version pinning / Zephyr alignment when builds break: search the [blog](https://zmk.dev/blog) for pinning and Zephyr updates; confirm `zmk` SHA matches expectations.

## Links vs step-by-step instructions

- **Default**: **Link to the official development docs** and give a **short, task-specific summary** (what to open, what concept applies). That stays accurate when ZMK changes.
- **Add concrete steps** when the user asks for them, when something is repo-specific (paths, shields, CI in this fork), or when the docs are navigational noise for a one-off task — still anchor steps to the same doc sections so they can verify details.

## What not to do

- Do not treat QMK/Vial concepts as ZMK facts; name the difference when relevant.
- Do not copy large passages from the docs into the codebase; link and paraphrase minimally.

## Additional resources

- [reference.md](reference.md)
