# Tipper TF - Code Sharing Guide

Diese Dokumentation beschreibt, welche Dateien und Verzeichnisse benötigt werden, um den Tipper TF Keyboard-Code mit anderen zu teilen, unabhängig von der Build-Umgebung (Docker, GitHub Actions, lokal, etc.).

## 📁 Übersicht: Benötigte Dateien und Verzeichnisse

### ✅ Essentielle Dateien (MUSS mitgeteilt werden)

#### 1. Board-Definition (`config/boards/tipper/tipper_tf/`)
Die komplette Board-Definition muss mitgeteilt werden:

```
config/boards/tipper/tipper_tf/
├── board.cmake              # Board-spezifische CMake-Konfiguration
├── board.yml                # Zephyr Board-YAML (für west)
├── Kconfig.board            # Board-Kconfig Definition
├── Kconfig.defconfig        # Board-spezifische Default-Konfiguration
├── Kconfig.tipper_tf        # Board-Kconfig (dupliziert für Kompatibilität)
├── tipper_tf.dts            # Device Tree Source (Hauptkonfiguration)
├── tipper_tf-layouts.dtsi   # Physical Layout Definition
├── tipper_tf.yaml           # Zephyr Board-YAML (für toolchain)
└── tipper_tf.zmk.yml        # ZMK Board-Metadaten
```

#### 2. Keyboard-Konfiguration (`keyboards/tipper_tf/`)
Die Keyboard-Konfiguration und Keymap:

```
keyboards/tipper_tf/
├── tipper_tf.conf           # Kconfig-Overlay (Display, Studio, etc.)
└── tipper_tf.keymap         # Keymap-Definition
```

#### 3. Display-Treiber (JD79653) (`zmk/app/module/drivers/display/`)
Alle Dateien für den JD79653 Display-Treiber:

```
zmk/app/module/drivers/display/
├── jd79653.c                # Haupttreiber-Code
├── jd79653_regs.h           # Register-Definitionen
├── Kconfig.jd79653          # Kconfig für JD79653 Treiber
├── CMakeLists.txt           # Build-Konfiguration (muss JD79653 enthalten!)
└── Kconfig                  # Haupt-Kconfig (muss Kconfig.jd79653 enthalten!)
```

#### 4. Device Tree Binding (`zmk/app/module/dts/bindings/display/`)
Das Device Tree Binding für JD79653:

```
zmk/app/module/dts/bindings/display/
└── gooddisplay,jd79653.yaml # Device Tree Binding für JD79653
```

#### 5. West Manifest (`config/west.yml`)
Falls Sie ein eigenes Repository haben, benötigen Sie:

```
config/west.yml              # West Manifest für das Config-Repository
```

### ❌ NICHT benötigte Dateien (können weggelassen werden)

- `.devcontainer/` - Docker-spezifische Konfiguration
- `scripts/` - Build-Skripte (sind Build-Umgebung-spezifisch)
- `build-test/` - Build-Outputs
- `for reference only/` - Referenz-Dateien (optional)
- `*.log` - Log-Dateien
- `zmk-tf2.code-workspace` - Editor-spezifische Konfiguration
- `optional/` - Optionale Module (falls nicht verwendet)

## 🔧 Integration in verschiedene Build-Umgebungen

### GitHub Actions

Die Dateien können direkt in ein GitHub-Repository kopiert werden. Beispiel-Workflow:

```yaml
name: Build Tipper TF

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Set up Zephyr environment
        uses: zmkfirmware/zmk-build-action@main
        with:
          board: tipper_tf
          keymap: tipper_tf
          config-dir: config
```

**Wichtig:** Stellen Sie sicher, dass die Dateistruktur erhalten bleibt:
- `config/boards/tipper/tipper_tf/` → muss im `config` Repository sein
- `keyboards/tipper_tf/` → kann in `config` oder separatem Repository sein
- `zmk/app/module/...` → muss im `zmk` Repository sein (als Fork oder Patch)

### Lokaler Build (ohne Docker)

Wenn jemand lokal baut, benötigt er:

1. **ZMK Repository** (geforkt oder mit Patches):
   - Die JD79653 Treiber-Dateien müssen im `zmk/app/module/drivers/display/` Verzeichnis sein
   - CMakeLists.txt und Kconfig müssen aktualisiert sein

2. **Config Repository**:
   - Board-Definition in `boards/tipper/tipper_tf/`
   - Keyboard-Konfiguration in `keyboards/tipper_tf/`

3. **Build-Befehl**:
```bash
west build -s zmk/app -b tipper_tf -- \
  -DZMK_CONFIG=/path/to/config \
  -DZMK_CONFIG_DIR=/path/to/config
```

### Docker Build

Für Docker benötigen Sie zusätzlich nur die Docker-spezifischen Dateien (`.devcontainer/`, `Dockerfile`, etc.), die aber **optional** sind, da jeder seine eigene Docker-Setup haben kann.

## 📋 Checkliste für Code-Sharing

### Board-Definition
- [ ] `config/boards/tipper/tipper_tf/board.cmake`
- [ ] `config/boards/tipper/tipper_tf/board.yml`
- [ ] `config/boards/tipper/tipper_tf/Kconfig.board`
- [ ] `config/boards/tipper/tipper_tf/Kconfig.defconfig`
- [ ] `config/boards/tipper/tipper_tf/Kconfig.tipper_tf`
- [ ] `config/boards/tipper/tipper_tf/tipper_tf.dts`
- [ ] `config/boards/tipper/tipper_tf/tipper_tf-layouts.dtsi`
- [ ] `config/boards/tipper/tipper_tf/tipper_tf.yaml`
- [ ] `config/boards/tipper/tipper_tf/tipper_tf.zmk.yml`

### Keyboard-Konfiguration
- [ ] `keyboards/tipper_tf/tipper_tf.conf`
- [ ] `keyboards/tipper_tf/tipper_tf.keymap`

### Display-Treiber (JD79653)
- [ ] `zmk/app/module/drivers/display/jd79653.c`
- [ ] `zmk/app/module/drivers/display/jd79653_regs.h`
- [ ] `zmk/app/module/drivers/display/Kconfig.jd79653`
- [ ] `zmk/app/module/drivers/display/CMakeLists.txt` (aktualisiert)
- [ ] `zmk/app/module/drivers/display/Kconfig` (aktualisiert)

### Device Tree Binding
- [ ] `zmk/app/module/dts/bindings/display/gooddisplay,jd79653.yaml`

### West Manifest (falls eigenes Config-Repo)
- [ ] `config/west.yml`

## 🔍 Wichtige Hinweise

### 1. Dateipfade müssen erhalten bleiben
Die relativen Pfade müssen exakt gleich sein. Wenn jemand die Dateien in sein Repository kopiert, muss die Struktur identisch sein.

### 2. CMakeLists.txt und Kconfig müssen aktualisiert sein
Stellen Sie sicher, dass `CMakeLists.txt` und `Kconfig` im `zmk/app/module/drivers/display/` Verzeichnis die JD79653 Einträge enthalten:

**CMakeLists.txt:**
```cmake
zephyr_library_sources_ifdef(CONFIG_JD79653 jd79653.c)
```

**Kconfig:**
```
rsource "Kconfig.jd79653"
```

### 3. Device Tree kompatibel halten
Das Device Tree in `tipper_tf.dts` muss `compatible = "gooddisplay,jd79653";` verwenden, nicht `gooddisplay,gdew0154m09`.

### 4. Konfiguration dokumentieren
Die `tipper_tf.conf` Datei enthält wichtige Einstellungen:
- Display-Konfiguration (1bpp, LVGL, etc.)
- ZMK Studio aktiviert
- USB Logging deaktiviert (incompatibel mit Studio)

Stellen Sie sicher, dass diese Einstellungen dokumentiert sind.

## 🚀 Schnellstart für Empfänger

Wenn jemand Ihren Code erhalten hat, sollte er:

1. **ZMK Repository forken/clonen** und die JD79653 Treiber-Dateien hinzufügen
2. **Config Repository klonen** mit der Board-Definition
3. **Keyboard-Konfiguration kopieren** (`tipper_tf.conf` und `tipper_tf.keymap`)
4. **Build durchführen** mit dem entsprechenden Build-System

## 📝 Beispiel: Git Repository-Struktur

```
tipper-tf-firmware/
├── README.md
├── .github/
│   └── workflows/
│       └── build.yml          # GitHub Actions Workflow
├── config/                     # Config Repository
│   ├── west.yml
│   ├── boards/
│   │   └── tipper/
│   │       └── tipper_tf/
│   │           └── [alle Board-Dateien]
│   └── keyboards/
│       └── tipper_tf/
│           ├── tipper_tf.conf
│           └── tipper_tf.keymap
└── zmk-patches/               # Patches für ZMK Repository
    └── display-driver-jd79653/
        ├── jd79653.c
        ├── jd79653_regs.h
        ├── Kconfig.jd79653
        └── gooddisplay,jd79653.yaml
```

## 🔗 Weitere Ressourcen

- [ZMK Board Support Guide](https://zmk.dev/docs/development/board-support)
- [ZMK Display Documentation](https://zmk.dev/docs/features/displays)
- [Zephyr Device Tree Guide](https://docs.zephyrproject.org/latest/build/dts/index.html)
