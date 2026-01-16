# 📦 Tipper TF - Minimale Dateiliste für Code-Sharing

Diese Dateien **MÜSSEN** mitgeteilt werden, damit andere das Keyboard bauen können, unabhängig von der Build-Umgebung.

## ✅ Essentielle Dateien (MUSS)

### 1. Board-Definition (9 Dateien)
```
config/boards/tipper/tipper_tf/
├── board.cmake
├── board.yml
├── Kconfig.board
├── Kconfig.defconfig
├── Kconfig.tipper_tf
├── tipper_tf.dts              # ⚠️ WICHTIG: Enthält Display-Konfiguration
├── tipper_tf-layouts.dtsi
├── tipper_tf.yaml
└── tipper_tf.zmk.yml
```

### 2. Keyboard-Konfiguration (2 Dateien)
```
keyboards/tipper_tf/
├── tipper_tf.conf              # ⚠️ WICHTIG: Display-Config, Studio, etc.
└── tipper_tf.keymap
```

### 3. Display-Treiber JD79653 (3 Dateien + 2 Modifikationen)
```
zmk/app/module/drivers/display/
├── jd79653.c                   # ⚠️ NEU: Custom Treiber
├── jd79653_regs.h              # ⚠️ NEU: Register-Definitionen
├── Kconfig.jd79653             # ⚠️ NEU: Kconfig
├── CMakeLists.txt              # ⚠️ MUSS MODIFIZIERT SEIN: jd79653.c enthalten
└── Kconfig                     # ⚠️ MUSS MODIFIZIERT SEIN: Kconfig.jd79653 enthalten
```

### 4. Device Tree Binding (1 Datei)
```
zmk/app/module/dts/bindings/display/
└── gooddisplay,jd79653.yaml    # ⚠️ NEU: Binding für Device Tree
```

### 5. West Manifest (1 Datei, optional)
```
config/west.yml                 # Nur falls eigenes Config-Repo
```

## 📋 Zusammenfassung

**Gesamt: ~16 Dateien** (davon 4 neue Dateien + 2 Modifikationen)

### Neue Dateien (müssen erstellt/bereitgestellt werden):
- `jd79653.c`
- `jd79653_regs.h`
- `Kconfig.jd79653`
- `gooddisplay,jd79653.yaml`

### Zu modifizierende Dateien (im ZMK-Repository):
- `zmk/app/module/drivers/display/CMakeLists.txt` - Zeile hinzufügen: `zephyr_library_sources_ifdef(CONFIG_JD79653 jd79653.c)`
- `zmk/app/module/drivers/display/Kconfig` - Zeile hinzufügen: `rsource "Kconfig.jd79653"`

### Standard-Dateien (Board-Config):
- Alle Dateien aus `config/boards/tipper/tipper_tf/`
- Alle Dateien aus `keyboards/tipper_tf/`

## 🚀 Quick Start für Empfänger

1. **Board-Definition** → In Config-Repository kopieren: `config/boards/tipper/tipper_tf/`
2. **Keyboard-Config** → In Config-Repository kopieren: `keyboards/tipper_tf/`
3. **Display-Treiber** → In ZMK-Repository kopieren: `zmk/app/module/drivers/display/`
4. **Device Tree Binding** → In ZMK-Repository kopieren: `zmk/app/module/dts/bindings/display/`
5. **Build-Konfiguration aktualisieren** → CMakeLists.txt und Kconfig modifizieren
6. **Build** → Standard ZMK Build-Prozess

## ❌ NICHT benötigt

- Docker-Konfiguration (`.devcontainer/`, `Dockerfile`)
- Build-Skripte (`scripts/`)
- Build-Outputs (`build/`, `build-test/`)
- Referenz-Dateien (`for reference only/`)
- Log-Dateien (`*.log`)

## 🔧 Build-Umgebung unabhängig

Die oben genannten Dateien funktionieren mit:
- ✅ GitHub Actions
- ✅ Docker (jede Docker-Setup)
- ✅ Lokaler Build
- ✅ Jede andere CI/CD-Umgebung

Die Build-Umgebung ist **nicht wichtig**, solange die Dateistruktur erhalten bleibt!
