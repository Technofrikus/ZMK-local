# Tipper TF - Code Sharing Guide (ZMK Module)

Diese Dokumentation beschreibt, wie der Tipper TF Keyboard-Code mithilfe des **ZMK Module** Konzepts mit anderen geteilt werden kann. Dies ist die sauberste Methode, da der ZMK-Core unberührt bleibt und alle Anpassungen (Treiber, Board-Definitionen) in einem eigenen Repository leben.

## 📦 Das ZMK Module Prinzip

Ein ZMK-Modul ist ein eigenständiges Git-Repository, das zusätzliche Funktionen (Boards, Treiber, Behaviors) enthält. ZMK erkennt diese Module automatisch, wenn sie in der `west.yml` deines Config-Repositories eingetragen sind.

**Vorteile:**
- Keine manuellen Dateikopien in den ZMK-Core nötig.
- Einfache Updates über Git.
- Saubere Trennung von Hardware-Definition und Nutzer-Konfiguration.

---

## 📁 Empfohlene Repository-Struktur (Module)

Wenn du ein Repository für das Tipper TF Modul erstellst, sollte es so aufgebaut sein:

```text
tipper-tf-module/
├── zephyr/
│   └── module.yml              # Identifiziert das Repo als Modul
├── boards/
│   └── tipper/
│       └── tipper_tf/          # Komplette Board-Definition
│           ├── board.cmake
│           ├── board.yml
│           ├── CMakeLists.txt
│           ├── Kconfig.board
│           ├── Kconfig.defconfig
│           ├── tipper_tf.dts
│           ├── tipper_tf-layouts.dtsi
│           ├── [Grafik- & Widget-Dateien]
│           └── ...
├── dts/
│   └── bindings/
│       └── display/
│           └── gooddisplay,jd79653.yaml  # Device Tree Binding
└── drivers/
    └── display/                # Custom JD79653 Treiber
        ├── jd79653.c
        ├── jd79653_regs.h
        ├── Kconfig.jd79653
        ├── CMakeLists.txt      # Muss jd79653.c enthalten
        └── Kconfig             # Muss Kconfig.jd79653 enthalten
```

---

## 🚀 Integration via `west.yml`

Um das Modul in einem ZMK-Setup zu nutzen, muss es in der `config/west.yml` des Nutzers registriert werden:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: dein-username
      url-base: https://github.com/dein-username
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    # Das Tipper TF Modul hinzufügen:
    - name: tipper-tf-module
      remote: dein-username
      revision: main
  self:
    path: config
```

Nach der Änderung muss `west update` ausgeführt werden.

---

## 📋 Checkliste: Benötigte Dateien für das Modul

### 1. Board-Definition (`boards/tipper/tipper_tf/`)
Alle Dateien in diesem Ordner sind für die korrekte Funktion der Hardware und des Displays (Grafiken) nötig:

- **Basis-Dateien:** `board.cmake`, `board.yml`, `Kconfig.board`, `Kconfig.defconfig`, `Kconfig.tipper_tf`, `tipper_tf.dts`, `tipper_tf-layouts.dtsi`, `tipper_tf.yaml`, `tipper_tf.zmk.yml`.
- **Grafiken & Widgets:**
  - `tipper_tf_status_screen.c` (Haupt-Display-Logik)
  - `tipper_tf_logo.c` & `tipper_tf_logo_tiles.c` (Logos)
  - `battery_status.c` & `battery_status.h` (Batterie-Widget)
  - `bt_rotated.c` (Bluetooth-Icons)
  - `RamseyALL20px.c` & `RamseyALL25px.c` (Fonts/Icons)
  - `RamseyBATP.c` (Batterie-Basis)
  - **Batterie-Grafiken (TBAT):** `TBAT00.c`, `TBAT00c.c`, `TBAT20.c`, `TBAT20c.c`, `TBAT40.c`, `TBAT40c.c`, `TBAT60.c`, `TBAT60c.c`, `TBAT80.c`, `TBAT80c.c`, `TBAT100.c`, `TBAT100c.c`.

### 2. Display-Treiber (`drivers/display/`)
- `jd79653.c`, `jd79653_regs.h`, `Kconfig.jd79653`.
- `CMakeLists.txt` (muss `zephyr_library_sources_ifdef(CONFIG_JD79653 jd79653.c)` enthalten).
- `Kconfig` (muss `rsource "Kconfig.jd79653"` enthalten).

### 3. Bindings (`dts/bindings/display/`)
- `gooddisplay,jd79653.yaml`.

---

## 🛠 Build-Befehl (Beispiel)

Sobald das Modul via `west` geladen ist, kann das Board wie jedes andere ZMK-Board gebaut werden:

```bash
west build -b tipper_tf -- -DZMK_CONFIG=/path/to/your/config
```

*Hinweis: Da das Board-Verzeichnis im Modul liegt, findet `west` es automatisch, sofern das Modul korrekt registriert ist.*

---

## 📝 Wichtige Hinweise für Nutzer
1. **Keymap**: Die Keymap (`tipper_tf.keymap`) und Konfiguration (`tipper_tf.conf`) verbleiben im persönlichen `config` Repository des Nutzers.
2. **Display-Support**: In der `tipper_tf.conf` muss `CONFIG_ZMK_DISPLAY=y` gesetzt sein, um den Treiber und die Widgets zu aktivieren.
3. **ZMK Studio**: Das Tipper TF Board unterstützt ZMK Studio. Es wird empfohlen, USB Logging zu deaktivieren (`CONFIG_ZMK_USB_LOGGING=n`), da dies mit der Studio-Kommunikation kollidieren kann.
