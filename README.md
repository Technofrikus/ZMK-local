# ZMK Universal Repository

Ein universelles ZMK User Config Repository mit Zephyr 4.1 / HWMv2 Support für die Entwicklung von ZMK-Firmware für verschiedene Keyboards.

## WICHTIG: Referenz-Dateien

**KRITISCH:** Die Dateien im Verzeichnis `for reference only/` dienen **NUR als Referenz** und werden **NIEMALS direkt verlinkt oder kopiert**. Sie werden nur als Informationsquelle für Neuimplementierungen verwendet. Das Repository ist vollständig unabhängig von diesen Referenz-Dateien.

## Übersicht

Dieses Repository enthält:

- **Zephyr 4.1 / HWMv2 Support** - Neueste Zephyr-Version mit Hardware Model V2
- **Tipper_TF Keyboard** - Neuimplementierung des Tipper_TF Keyboards
- **Phasenweise Implementierung:**
  - **Phase 1:** Grundkonfiguration OHNE Display, MIT ZMK Studio ✅
  - **Phase 2:** Display-Treiber Integration (geplant)
- **Docker (VS Code Dev Container)** - Primäre Build-Methode
- **Local Host Build-Skripte** - Alternative Build-Methode

## Repository-Struktur

```
ZMK-tf2/
├── config/
│   ├── west.yml                    # ZMK Manifest mit Zephyr 4.1
│   └── boards/
│       └── arm/
│           └── tipper_tf/          # Board-Definition (HWMv2)
├── keyboards/
│   └── tipper_tf/
│       ├── tipper_tf.keymap        # Keymap
│       └── tipper_tf.conf          # Config (Phase 1: Studio, NO Display)
├── .devcontainer/                  # VS Code Dev Container Setup
│   ├── devcontainer.json
│   └── Dockerfile
├── .vscode/                        # VS Code Settings
│   └── settings.json
├── scripts/                        # Build-Hilfsskripte
│   ├── build.sh                    # Build-Skript für Local Host
│   ├── setup-local.sh              # Setup-Skript für Local Host
│   └── test-build-docker.sh        # Test-Build mit Docker
└── README.md                       # Diese Datei
```

## Ersteinrichtung auf einem neuen Rechner

Diese Anleitung beschreibt die komplette Einrichtung der ZMK-Entwicklungsumgebung von Grund auf.

### Schritt 1: Docker installieren

**macOS mit Homebrew:**
```bash
brew install --cask docker
```

**Oder manuell:**
- Download von https://www.docker.com/products/docker-desktop
- Docker Desktop installieren und starten
- Warten, bis Docker vollständig gestartet ist (Wal-Icon in der Menüleiste)

**Prüfen:**
```bash
docker --version
docker ps  # Sollte ohne Fehler funktionieren
```

**Hinweis:** Falls `docker ps` einen Fehler zeigt ("failed to connect to docker daemon"), starte Docker Desktop manuell und warte, bis es vollständig geladen ist.

### Schritt 2: West installieren (für Local Host, optional)

**macOS mit Homebrew:**
```bash
# pipx installieren (falls noch nicht vorhanden)
brew install pipx

# west installieren
pipx install west

# PATH aktualisieren (dauerhaft in ~/.zshrc oder ~/.bashrc)
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

**Prüfen:**
```bash
west --version
```

**Wichtig:** Auf macOS mit Python 3.14+ funktioniert `pip3 install --user` nicht mehr (externally-managed-environment). Verwende stattdessen `pipx`.

### Schritt 3: Repository klonen (falls noch nicht geschehen)

```bash
git clone <repository-url> ZMK-tf2
cd ZMK-tf2
```

### Schritt 4: Test der Build-Umgebung

**WICHTIG:** Bevor du mit dem Tipper TF Keyboard arbeitest, solltest du die Build-Umgebung mit einem Standard-Keyboard testen!

Führe den Test-Build aus:
```bash
./scripts/test-build-docker.sh
```

**Erwartete Ausgabe bei Erfolg:**
```
✓✓✓ ZMK build environment test PASSED! ✓✓✓
The build environment is working correctly.
You can now build your Tipper TF keyboard.
```

**Wichtige Erkenntnisse aus dem Setup:**
- ✅ Docker Image: `zmkfirmware/zmk-build-arm:stable` (nicht `zmk-dev-arm:latest`)
- ✅ Board-Namen in Zephyr 4.1: Einfacher Name (z.B. `nice_nano` statt `nicekeyboards/nice_nano`)
- ✅ West auf macOS: Verwende `pipx` statt `pip3 install --user`
- ✅ Docker Desktop muss laufen, bevor Container gestartet werden können

Falls der Test erfolgreich ist, ist die Umgebung bereit! Du kannst jetzt mit dem Tipper TF Keyboard arbeiten.

## Setup (Detaillierte Anleitungen)

### Voraussetzungen

- **Docker Desktop** installiert und gestartet (siehe Ersteinrichtung)
- **Visual Studio Code** mit Extension "Remote - Containers" (optional, für Dev Container)
- **Homebrew** (für macOS) - [Installation](https://brew.sh)

## Test der Build-Umgebung (Detailliert)

### Option 1: Mit Docker (Empfohlen)

**Einfachste Methode - Test-Build direkt mit Docker:**

1. **Docker Desktop starten** (wenn noch nicht gestartet)
2. **Test-Skript ausführen:**
   ```bash
   ./scripts/test-build-docker.sh
   ```
   Dieses Skript:
   - Wartet automatisch auf Docker
   - Führt den Test-Build in einem Container aus
   - Baut automatisch ein Standard-Keyboard (`nice_nano` mit `corne_left`)
   - Zeigt, ob die Umgebung funktioniert

**Alternative: VS Code Dev Container**

1. **Docker Desktop starten**
2. **VS Code öffnen** und Dev Container starten
3. **Im Container-Terminal:**
   ```bash
   ./scripts/test-build.sh
   ```

### Option 2: Local Host

**Voraussetzungen:**
- West installiert (siehe Schritt 2 oben)
- Zephyr SDK installiert

1. **Zephyr SDK installieren:**
   - Download von https://github.com/zephyrproject-rtos/sdk-ng/releases
   - Installieren und `ZEPHYR_SDK_INSTALL_DIR` setzen:
     ```bash
     export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk
     # Dauerhaft in ~/.zshrc oder ~/.bashrc speichern
     echo 'export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk' >> ~/.zshrc
     ```

2. **Test-Build ausführen:**
   ```bash
   ./scripts/test-build.sh
   ```

**Was das Test-Skript macht:**
- Prüft, ob alle Tools verfügbar sind
- Initialisiert das west workspace automatisch (falls nötig)
- Baut ein Standard-Keyboard (`nice_nano` + `corne_left`)
- Zeigt an, ob die Umgebung korrekt funktioniert

## Firmware bauen

### Option 1: Docker (Empfohlen - Einfachste Methode)

**Für schnelle Builds ohne VS Code:**

```bash
# Test-Build (optional, aber empfohlen)
./scripts/test-build-docker.sh

# Tipper TF bauen
docker run --rm \
  -v "$(pwd):/workspaces/ZMK-tf2" \
  -w /workspaces/ZMK-tf2 \
  docker.io/zmkfirmware/zmk-build-arm:stable \
  bash -c "west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf"
```

**Oder mit VS Code Dev Container:**

1. **Docker Desktop starten** (falls noch nicht läuft)

2. **VS Code öffnen:**
   ```bash
   code .
   ```

3. **Dev Container öffnen:**
   - VS Code sollte automatisch vorschlagen, den Container zu öffnen
   - Oder: `F1` → "Remote-Containers: Reopen in Container"
   - Beim ersten Mal wird das Docker Image heruntergeladen (kann einige Minuten dauern)

4. **West Workspace initialisieren** (beim ersten Mal):
   - Im Container-Terminal:
   ```bash
   west init -l config
   west update
   west zephyr-export
   ```

5. **Firmware bauen:**
   ```bash
   west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf
   ```

### Option 2: Local Host

**Voraussetzungen:**
- Zephyr SDK installiert
- West installiert (via pipx, siehe Ersteinrichtung)

1. **Zephyr SDK installieren:**
   - Download von https://github.com/zephyrproject-rtos/sdk-ng/releases
   - Installieren und `ZEPHYR_SDK_INSTALL_DIR` setzen:
     ```bash
     export ZEPHYR_SDK_INSTALL_DIR=/path/to/zephyr-sdk
     ```

2. **Setup-Skript ausführen** (beim ersten Mal):
   ```bash
   ./scripts/setup-local.sh
   ```

3. **Firmware bauen:**
   ```bash
   ./scripts/build.sh tipper_tf tipper_tf
   ```

## Build-Kommandos

### Docker (VS Code Dev Container)

```bash
# Im Container-Terminal
west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf
```

### Local Host

```bash
# Mit Build-Skript
./scripts/build.sh tipper_tf tipper_tf

# Oder direkt mit west
west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=$(pwd)/keyboards/tipper_tf
```

## Flashen der Firmware

Nach erfolgreichem Build:

```bash
# Mit west
west flash

# Oder mit nrfjprog (für nRF52840)
nrfjprog -f nrf52 --program build/zephyr/zephyr.hex --chiperase --reset
```

## Phase 1: Grundkonfiguration (OHNE Display, MIT ZMK Studio)

Phase 1 ist implementiert und getestet. Die Konfiguration enthält:

- ✅ Board-Definition (HWMv2)
- ✅ Keymap mit mehreren Layern
- ✅ ZMK Studio Support
- ✅ USB und BLE Support
- ✅ Battery-Voltage-Divider
- ❌ **KEIN Display** (wird in Phase 2 hinzugefügt)

### Erfolgskriterien Phase 1

- [x] Board kompiliert erfolgreich
- [x] Firmware kann geflasht werden
- [ ] Keyboard funktioniert (Tastatur-Eingaben) - **Zu testen**
- [ ] ZMK Studio kann sich verbinden - **Zu testen**
- [ ] BLE und USB funktionieren - **Zu testen**

## Phase 2: Display-Integration (Geplant)

**Nur nach erfolgreicher Phase 1:**

1. Display-Treiber aus Referenz analysieren
2. Display-Konfiguration in Board-Definition integrieren
3. Config für Display aktualisieren
4. Display-Funktionalität testen

## Wichtige Migrationen (Zephyr 4.1)

### Board-Revisionen

Zephyr 4.1 verwendet Board-Revisionen statt separater Board-Definitionen:
- Alte Syntax: `nice_nano_v2`
- Neue Syntax: `nice_nano@2.0.0` oder `nice_nano` (default)

### HWMv2 Konvertierung

Board-Dateien sind in `boards/arm/<board>/` strukturiert:
- `board.cmake` - CMake-Konfiguration
- `Kconfig.defconfig` - Board-spezifische Kconfig
- `<board>.dts` - Devicetree-Definition
- `<board>.yaml` - Board-Metadaten
- `<board>.zmk.yml` - ZMK Hardware-Metadaten

### Kconfig → Devicetree

Einige Konfigurationen wurden von Kconfig zu Devicetree verschoben:
- DC/DC Konfiguration jetzt in `.dts` Dateien
- `CONFIG_WS2812_STRIP=y` wird automatisch aktiviert (nicht mehr nötig)

## Troubleshooting

### Docker-Probleme

1. **Docker Daemon läuft nicht**
   ```bash
   # Docker Desktop manuell starten
   open -a Docker
   
   # Prüfen ob Docker läuft
   docker ps
   ```

2. **Docker Image nicht gefunden**
   - Stelle sicher, dass du `zmkfirmware/zmk-build-arm:stable` verwendest
   - Image manuell pullen: `docker pull zmkfirmware/zmk-build-arm:stable`

3. **Docker Container startet nicht (VS Code)**
   - Prüfe, ob Docker Desktop läuft
   - Prüfe Docker-Logs in VS Code
   - Container manuell neu bauen: `F1` → "Remote-Containers: Rebuild Container"

### Build-Fehler

1. **West workspace nicht initialisiert**
   ```bash
   west init -l config
   west update
   west zephyr-export
   ```

2. **Zephyr SDK nicht gefunden (Local Host)**
   - Prüfe `ZEPHYR_SDK_INSTALL_DIR` Umgebungsvariable
   - Installiere Zephyr SDK falls nicht vorhanden
   - Setze die Variable in deiner Shell-Konfiguration (`.zshrc` oder `.bashrc`)

3. **West nicht gefunden (Local Host)**
   - Prüfe, ob west installiert ist: `which west`
   - Falls nicht: `pipx install west`
   - PATH aktualisieren: `export PATH="$HOME/.local/bin:$PATH"`

4. **Board nicht gefunden**
   - In Zephyr 4.1 / HWMv2 werden Boards einfach mit ihrem Namen referenziert
   - Beispiel: `nice_nano` statt `nicekeyboards/nice_nano`
   - Verfügbare Boards anzeigen: `west boards`

5. **Python externally-managed-environment Fehler (macOS)**
   - Verwende `pipx` statt `pip3 install --user`:
     ```bash
     brew install pipx
     pipx install west
     ```

### ZMK Studio Verbindungsprobleme

1. **Studio kann sich nicht verbinden**
   - Prüfe, ob `CONFIG_ZMK_STUDIO=y` in Config aktiviert ist
   - Prüfe USB-Verbindung
   - Prüfe, ob Firmware korrekt geflasht wurde

2. **Keyboard bootet locked**
   - Setze `CONFIG_ZMK_STUDIO_LOCKING=n` in Config
   - Flash Firmware erneut

## Weitere Keyboards hinzufügen

Um weitere Keyboards hinzuzufügen:

1. Erstelle Verzeichnis `keyboards/<keyboard_name>/`
2. Erstelle `<keyboard_name>.keymap` und `<keyboard_name>.conf`
3. Falls nötig, erstelle Board-Definition in `config/boards/arm/<board>/`
4. Verwende `./scripts/build.sh <keyboard> <board>` zum Bauen

## Wichtige Regeln

- **NIEMALS** Dateien aus `for reference only/` direkt kopieren oder verlinken
- **NUR** als Informationsquelle für Neuimplementierung verwenden
- Alle Dateien werden neu geschrieben, basierend auf Referenz-Informationen
- Repository ist vollständig unabhängig von Referenz-Dateien

## Links

- [ZMK Dokumentation](https://zmk.dev/docs)
- [Zephyr 4.1 Upgrade Guide](https://zmk.dev/blog/2025/12/09/zephyr-4-1)
- [ZMK GitHub](https://github.com/zmkfirmware/zmk)

## Lizenz

MIT License - Siehe LICENSE Datei für Details
