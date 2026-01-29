# Tipper TF - Code Sharing Guide (ZMK Module)

This documentation describes how to share the Tipper TF keyboard code using the **ZMK Module** concept. This is the cleanest method, as the ZMK core remains untouched and all customizations (drivers, board definitions) live in their own repository.

## 📦 The ZMK Module Principle

A ZMK module is a standalone Git repository containing additional features (boards, drivers, behaviors). ZMK automatically recognizes these modules when they are registered in the `west.yml` of your config repository.

**Advantages:**
- No manual file copying into the ZMK core required.
- Easy updates via Git.
- Clean separation of hardware definition and user configuration.

---

## 📁 Recommended Repository Structure (Module)

When creating a repository for the Tipper TF module, it should be structured as follows:

```text
tipper-tf-module/
├── zephyr/
│   └── module.yml              # Identifies the repo as a module
├── boards/
│   └── tipper/
│       └── tipper_tf/          # Complete board definition
│           ├── board.cmake
│           ├── board.yml
│           ├── CMakeLists.txt
│           ├── Kconfig.board
│           ├── Kconfig.defconfig
│           ├── tipper_tf.dts
│           ├── tipper_tf-layouts.dtsi
│           ├── [Graphics & Widget files]
│           └── ...
├── dts/
│   └── bindings/
│       └── display/
│           └── gooddisplay,jd79653.yaml  # Device Tree Binding
└── drivers/
    └── display/                # Custom JD79653 driver
        ├── jd79653.c
        ├── jd79653_regs.h
        ├── Kconfig.jd79653
        ├── CMakeLists.txt      # Must contain jd79653.c
        └── Kconfig             # Must contain Kconfig.jd79653
```

---

## 🚀 Integration via `west.yml`

To use the module in a ZMK setup, it must be registered in the user's `config/west.yml`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: your-username
      url-base: https://github.com/your-username
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    # Add the Tipper TF module:
    - name: tipper-tf-module
      remote: your-username
      revision: main
  self:
    path: config
```

After the change, run `west update`.

---

## 📋 Checklist: Required Files for the Module

### 1. Board Definition (`boards/tipper/tipper_tf/`)
All files in this folder are necessary for the correct function of the hardware and the display (graphics):

- **Base Files:** `board.cmake`, `board.yml`, `Kconfig.board`, `Kconfig.defconfig`, `Kconfig.tipper_tf`, `tipper_tf.dts`, `tipper_tf-layouts.dtsi`, `tipper_tf.yaml`, `tipper_tf.zmk.yml`.
- **Graphics & Widgets:**
  - `tipper_tf_status_screen.c` (Main display logic)
  - `tipper_tf_logo.c` & `tipper_tf_logo_tiles.c` (Logos)
  - `battery_status.c` & `battery_status.h` (Battery widget)
  - `bt_rotated.c` (Bluetooth icons)
  - `RamseyALL20px.c` & `RamseyALL25px.c` (Fonts/Icons)
  - `RamseyBATP.c` (Battery base)
  - **Battery Graphics (TBAT):** `TBAT00.c`, `TBAT00c.c`, `TBAT20.c`, `TBAT20c.c`, `TBAT40.c`, `TBAT40c.c`, `TBAT60.c`, `TBAT60c.c`, `TBAT80.c`, `TBAT80c.c`, `TBAT100.c`, `TBAT100c.c`.

### 2. Display Driver (`drivers/display/`)
- `jd79653.c`, `jd79653_regs.h`, `Kconfig.jd79653`.
- `CMakeLists.txt` (must contain `zephyr_library_sources_ifdef(CONFIG_JD79653 jd79653.c)`).
- `Kconfig` (must contain `rsource "Kconfig.jd79653"`).

### 3. Bindings (`dts/bindings/display/`)
- `gooddisplay,jd79653.yaml`.

---

## 🛠 Build Command (Example)

Once the module is loaded via `west`, the board can be built like any other ZMK board:

```bash
west build -b tipper_tf -- -DZMK_CONFIG=/path/to/your/config
```

*Note: Since the board directory is in the module, `west` will find it automatically if the module is correctly registered.*

---

## 📝 Important Notes for Users
1. **Keymap**: The keymap (`tipper_tf.keymap`) and configuration (`tipper_tf.conf`) remain in the user's personal `config` repository.
2. **Display Support**: `CONFIG_ZMK_DISPLAY=y` must be set in `tipper_tf.conf` to activate the driver and widgets.
3. **ZMK Studio**: The Tipper TF board supports ZMK Studio. It is recommended to disable USB logging (`CONFIG_ZMK_USB_LOGGING=n`) as it can interfere with Studio communication.
