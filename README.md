# ZMK Universal Repository

Ein universelles ZMK User Config Repository mit Zephyr 4.1 / HWMv2 Support für die Entwicklung von ZMK-Firmware für verschiedene Keyboards.

## Übersicht

Dieses Repository enthält:

- **Zephyr 4.1 / HWMv2 Support** - Neueste Zephyr-Version mit Hardware Model V2
- **Modularer Aufbau:** Einfaches Hinzufügen weiterer Keyboards und Board-Definitionen
- **Docker (VS Code Dev Container)** - Primäre Build-Methode
- **Local Host Build-Skripte** - Alternative Build-Methode

## Repository-Struktur

```
ZMK-tf2/
├── config/
│   ├── west.yml                    # ZMK Manifest mit Zephyr 4.1
│   └── boards/                     # Board-Definition (HWMv2)
│       └── arm/
│           └── keyboard-name/ 
├── keyboards/                      # Keymap
│   └── keyboard-name/
│       ├── keyboard-name.keymap        
│       └── keyboard-name.conf        
├── .devcontainer/                  # VS Code Dev Container Setup
│   ├── devcontainer.json
│   └── Dockerfile
├── .vscode/                        # VS Code Settings
│   └── settings.json
├── scripts/                        # Build-Hilfsskripte
│   ├── build.sh                    # Build-Skript
│   ├── setup-local.sh              # Setup-Skript für ohne Docker, nicht empfohlen
│   └── test-build-docker.sh        # Test-Build mit Docker, ob Umgebung korrekt eingerichtet ist
```

## Ersteinrichtung auf einem neuen Rechner

Diese Anleitung beschreibt die komplette Einrichtung der ZMK-Entwicklungsumgebung von Grund auf.

### Schritt 1: Docker installieren

**macOS mit Homebrew:**

```bash
brew install --cask docker
```

**Oder manuell:**

- Download von [https://www.docker.com/products/docker-desktop](https://www.docker.com/products/docker-desktop)
- Docker Desktop installieren und starten
- Warten, bis Docker vollständig gestartet ist (Wal-Icon in der Menüleiste)

**Prüfen:**

```bash
docker --version
docker ps  # Sollte ohne Fehler funktionieren
```

**Hinweis:** Falls `docker ps` einen Fehler zeigt ("failed to connect to docker daemon"), starte Docker Desktop manuell und warte, bis es vollständig geladen ist.


### Schritt 2: Repository klonen (falls noch nicht geschehen)

```bash
git clone https://github.com/Technofrikus/ZMK-local
cd ZMK-local
```

### Schritt 4: Test der Build-Umgebung

**WICHTIG:** Build-Umgebung mit einem Standard-Keyboard testen

Führe den Test-Build aus:

```bash
./scripts/test-build-docker.sh
```

**Erwartete Ausgabe bei Erfolg:**

```
✓✓✓ ZMK build environment test PASSED! ✓✓✓
The build environment is working correctly.
You can now build your keyboard.
```

**Wichtige Erkenntnisse aus dem Setup:**

- ✅ Docker Image: `zmkfirmware/zmk-build-arm:stable` (nicht `zmk-dev-arm:latest`)
- ✅ Board-Namen in Zephyr 4.1: Einfacher Name (z.B. `nice_nano` statt `nicekeyboards/nice_nano`)
- ✅ Docker Desktop muss laufen, bevor Container gestartet werden können

Falls der Test erfolgreich ist, ist die Umgebung bereit! Du kannst jetzt mit dem Keyboard arbeiten.

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

**Was das Test-Skript macht:**

- Prüft, ob alle Tools verfügbar sind
- Initialisiert das west workspace automatisch (falls nötig)
- Baut ein Standard-Keyboard (`nice_nano` + `corne_left`)
- Zeigt an, ob die Umgebung korrekt funktioniert

## Firmware bauen

### Komfort-Weg (Empfohlen)

Nutze das Build-Skript, das alle Docker-Befehle kapselt. Du musst dafür `west` nicht lokal installiert haben, nur Docker muss laufen.

```bash
# BeispieL:Planckton bauen (Standard: nice_nano)
./scripts/build.sh planckton

# Tipper TF bauen
./scripts/build.sh tipper_tf
```

**Was das Skript macht:**

- Startet einen Docker-Container mit der passenden ZMK-Umgebung.
- Erkennt automatisch das richtige Board (z.B. `nice_nano` für Planckton).
- Setzt den `BOARD_ROOT` korrekt, damit deine eigenen Hardware-Definitionen in `config/` gefunden werden.
- Kopiert die fertige `.uf2` Datei automatisch in den Ordner `output/` und benennt sie sinnvoll (z.B. `planckton_nice_nano.uf2`).

### Diagnose & Fehlerbehebung

Falls der Build fehlschlägt oder du Probleme mit deiner Umgebung vermutest, gibt es Diagnose-Skripte:

```bash
# Testet die Docker-Umgebung mit einem Standard-Keyboard (Corne)
./scripts/test-build-docker.sh
```

*Nutze dieses Skript, um zu prüfen, ob ein Fehler an deinem Code oder an der Docker-Installation liegt. Wenn dieser Test erfolgreich ist, ist deine Umgebung korrekt eingerichtet.*

### Manueller Docker-Weg

Falls du volle Kontrolle über den Befehl benötigst:

```bash
docker run --rm \
  -v "$(pwd):/workspaces/ZMK-tf2" \
  -w /workspaces/ZMK-tf2 \
  docker.io/zmkfirmware/zmk-build-arm:stable \
  bash -c "west zephyr-export && west build -p always -s zmk/app -b nice_nano -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/planckton -DSHIELD=planckton"
```

### Option 2: VS Code Dev Container

1. **Docker Desktop starten**
2. **VS Code öffnen** und Dev Container starten (`F1` → "Remote-Containers: Reopen in Container")
3. **Im Container-Terminal:**
  ```bash
   west build -p always -s zmk/app -b nice_nano -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/planckton -DSHIELD=planckton
  ```

## Build-Kommandos

### Docker (VS Code Dev Container)

```bash
# Im Container-Terminal
west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf
```

## Flashen der Firmware

Nach erfolgreichem Build:

```bash
# Mit west
west flash

# Oder mit nrfjprog (für nRF52840)
nrfjprog -f nrf52 --program build/zephyr/zephyr.hex --chiperase --reset
```

## ZMK Update & Wartung

Um die ZMK-Firmware (Core) auf den neuesten Stand zu bringen (entsprechend der `config/west.yml`), muss der Befehl `west update` ausgeführt werden.

### Option 1: Mit Docker (Empfohlen)

Wenn du `west` nicht lokal installiert hast, kannst du das Update einfach über Docker ausführen:

**Einmaliger Befehl:**

```bash
docker run --rm \
  -v "$(pwd):/workspaces/ZMK-tf2" \
  -w /workspaces/ZMK-tf2 \
  docker.io/zmkfirmware/zmk-build-arm:stable \
  bash -c "west init -l config && west update"
```

**Interaktives Arbeiten im Container:**
Wenn du im Container bleiben möchtest, um mehrere Befehle auszuführen:

```bash
docker run --rm -it \
  -v "$(pwd):/workspaces/ZMK-tf2" \
  -w /workspaces/ZMK-tf2 \
  docker.io/zmkfirmware/zmk-build-arm:stable \
  bash
```

*Nach dem Start bist du im Container und kannst Befehle wie `west update` oder `west build` direkt eingeben.*

### Option 2: Im VS Code Dev Container

Falls du den Dev Container nutzt, öffne einfach ein Terminal **im Container** und gib ein:

```bash
west update
```

## Weitere Keyboards hinzufügen

Um weitere Keyboards hinzuzufügen:

1. Erstelle Verzeichnis `keyboards/<keyboard_name>/`
2. Erstelle `<keyboard_name>.keymap` und `<keyboard_name>.conf`
3. Falls nötig, erstelle Board-Definition in `config/boards/arm/<board>/`
4. Verwende `./scripts/build.sh <keyboard> <board>` zum Bauena

## Links

- [ZMK Dokumentation](https://zmk.dev/docs)
- [Zephyr 4.1 Upgrade Guide](https://zmk.dev/blog/2025/12/09/zephyr-4-1)
- [ZMK GitHub](https://github.com/zmkfirmware/zmk)

## Lizenz

MIT License - Siehe LICENSE Datei für Details