# ZMK — reference (development docs)

## Versions

| Use | URL |
| --- | --- |
| **Development (default for this repo)** | https://zmk.dev/docs |
| v0.3 release snapshot only if requested | https://v0-3-branch.zmk.dev/docs/ |

## Official

- Blog: https://zmk.dev/blog  
- Upstream source: https://github.com/zmkfirmware/zmk  

## ZMK Studio (always relevant)

- Feature page: https://zmk.dev/docs/features/studio  
- Include Studio whenever discussing keymap changes, testing, or end-user workflows.

## Typical doc sections

- Getting Started / Installing ZMK / Supported Hardware  
- Keymaps, layers, combos  
- Behaviors (hold-tap, tap-dance, macros, mouse keys, outputs, etc.)  
- Configuration (Kconfig, devicetree)  
- Features: split, Bluetooth, battery, encoders, pointing  

## Checklist

1. Prefer **zmk.dev/docs** (development), not v0-3-branch, unless the user wants the release docs.  
2. Mention **ZMK Studio** for keymap/runtime workflows.  
3. On upgrade or weird build errors, check **blog** + pinned ZMK revision vs Zephyr.
