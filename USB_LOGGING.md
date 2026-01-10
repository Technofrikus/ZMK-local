# USB Logging für Display Debugging

Diese Anleitung beschreibt, wie USB Logging für das Debugging des GDEW0154M09 E-Paper Displays verwendet wird.

## Übersicht

USB Logging ermöglicht es, Debug-Ausgaben vom Keyboard über USB zu empfangen. Dies ist besonders nützlich, um das Verhalten des Display-Treibers zu analysieren, wenn das Display keine Ausgabe zeigt.

**Wichtig:** USB Logging und ZMK Studio können nicht gleichzeitig aktiviert sein, da beide USB CDC-ACM verwenden. Für Display-Debugging wird ZMK Studio temporär deaktiviert.

## Voraussetzungen

- macOS (für diese Anleitung)
- `tio` installiert (via Homebrew: `brew install tio`)
- Keyboard mit geflashtem Firmware-Image mit aktiviertem USB Logging

## tio Installation

Falls `tio` noch nicht installiert ist:

```bash
brew install tio
```

## USB Device finden

Nach dem Flashen der Firmware mit aktiviertem USB Logging sollte ein USB CDC-ACM Device erkannt werden:

```bash
ls /dev/tty.usbmodem*
```

Typische Ausgabe:
```
/dev/tty.usbmodem14401
```

## tio starten

### Einfache Verbindung

```bash
sudo tio /dev/tty.usbmodem14401
```

### Mit automatischem Logging

```bash
sudo tio --log --log-file=zmk-display-debug.log --log-strip /dev/tty.usbmodem14401
```

**Optionen:**
- `--log`: Aktiviert automatisches Logging in eine Datei
- `--log-file=zmk-display-debug.log`: Spezifiziert den Log-Dateinamen
- `--log-strip`: Entfernt Control-Characters und Escape-Sequenzen für saubere Logs
- `--log-append`: Hängt an bestehende Log-Datei an (statt zu überschreiben)

### Beispiel mit allen Optionen

```bash
sudo tio --log --log-file=zmk-display-debug.log --log-strip --log-append /dev/tty.usbmodem14401
```

## tio Konfigurationsdatei

Für persistente Einstellungen kann eine Konfigurationsdatei erstellt werden:

**Datei:** `~/.config/tio/config`

```
log = yes
log-file = zmk-display-debug.log
log-append = yes
log-strip = yes
```

Mit dieser Konfiguration startet `tio` automatisch mit Logging, wenn nur das Device angegeben wird:

```bash
sudo tio /dev/tty.usbmodem14401
```

## Erwartete Log-Ausgaben

Nach dem Flashen und Verbinden mit `tio` sollten folgende Logs erscheinen:

### Display-Treiber Initialisierung

```
[00:00:00.123,456] <inf> gdew0154m09: GDEW0154M09 initialized
```

### SPI-Bus Status

Falls SPI nicht ready ist:
```
[00:00:00.234,567] <err> gdew0154m09: SPI bus spi0 not ready
```

### GPIO Status

Falls GPIOs nicht ready sind:
```
[00:00:00.345,678] <err> gdew0154m09: Reset GPIO not ready
[00:00:00.345,678] <err> gdew0154m09: DC GPIO not ready
[00:00:00.345,678] <err> gdew0154m09: Busy GPIO not ready
```

### Display Updates

Bei jedem Display-Update:
```
[00:00:01.456,789] <dbg> gdew0154m09: Update display
```

### SPI-Transaktionsfehler

Falls SPI-Transaktionen fehlschlagen:
```
[00:00:02.567,890] <err> gdew0154m09: SPI write failed: -5
```

## Debugging-Strategie

### 1. Display-Treiber Initialisierung prüfen

**Frage:** Wird `gdew0154m09_init()` aufgerufen?

**Zu suchen:** `GDEW0154M09 initialized` in den Logs

**Falls nicht vorhanden:**
- Prüfe, ob Display-Treiber im Build enthalten ist
- Prüfe Device Tree Konfiguration (`display: gdew0154m09@0`)

### 2. SPI-Kommunikation prüfen

**Frage:** Werden SPI-Transaktionen erfolgreich durchgeführt?

**Zu suchen:** Keine `SPI write failed` oder `SPI bus not ready` Fehler

**Falls Fehler:**
- Prüfe SPI-Konfiguration in Device Tree (`&spi0`)
- Prüfe SPI-Pins (SCK, MOSI, MISO, CS)
- Prüfe `spi-max-frequency` (sollte 4000000 sein)

### 3. GPIO-Signale prüfen

**Frage:** Werden Reset, DC, Busy korrekt gesetzt?

**Zu suchen:** Keine `GPIO not ready` Fehler

**Falls Fehler:**
- Prüfe GPIO-Pins in Device Tree:
  - `dc-gpios = <&gpio0 6 GPIO_ACTIVE_LOW>`
  - `reset-gpios = <&gpio1 13 GPIO_ACTIVE_LOW>`
  - `busy-gpios = <&gpio1 15 (GPIO_ACTIVE_LOW | GPIO_PULL_UP)>`
- Prüfe, ob GPIOs korrekt konfiguriert sind

### 4. Display Update prüfen

**Frage:** Wird `gdew0154m09_update_display()` aufgerufen?

**Zu suchen:** `Update display` Debug-Messages

**Falls nicht vorhanden:**
- Prüfe LVGL-Integration
- Prüfe `CONFIG_ZMK_DISPLAY_TICK_PERIOD_MS`
- Prüfe, ob Display von LVGL verwendet wird

### 5. LVGL Integration prüfen

**Frage:** Wird das Display von LVGL verwendet?

**Zu suchen:** LVGL-bezogene Logs (falls aktiviert)

**Falls nicht:**
- Prüfe `CONFIG_ZMK_DISPLAY=y`
- Prüfe `zephyr,display = &display;` in Device Tree
- Prüfe LVGL-Konfiguration

## Häufige Probleme

### Problem: Keine Logs nach dem Flashen

**Lösung:**
- Prüfe, ob USB Logging in Config aktiviert ist (`CONFIG_ZMK_USB_LOGGING=y`)
- Prüfe Device Tree (`zephyr,console = &usb_logging_uart`)
- Warte 8 Sekunden nach dem Boot (wegen `CONFIG_LOG_PROCESS_THREAD_STARTUP_DELAY_MS=8000`)
- Prüfe, ob Device erkannt wird: `ls /dev/tty.usbmodem*`

### Problem: SPI-Bus nicht ready

**Lösung:**
- Prüfe SPI-Konfiguration in Device Tree
- Prüfe, ob `CONFIG_SPI=y` in Config aktiviert ist
- Prüfe SPI-Pins und Pinmux-Konfiguration

### Problem: GPIO nicht ready

**Lösung:**
- Prüfe GPIO-Pins in Device Tree
- Prüfe, ob GPIOs nicht von anderen Peripherals verwendet werden
- Prüfe GPIO-Konfiguration (Active High/Low, Pull-Up/Down)

### Problem: Keine Display-Updates

**Lösung:**
- Prüfe LVGL-Integration
- Prüfe `CONFIG_ZMK_DISPLAY_TICK_PERIOD_MS`
- Prüfe Display-Tick-Konfiguration
- Prüfe, ob Display von LVGL verwendet wird

## tio Tastenkombinationen

Während `tio` läuft:

- `Ctrl-t` + `q`: Beendet tio
- `Ctrl-t` + `f`: Toggle Logging (ein/aus)
- `Ctrl-t` + `c`: Toggle Local Echo
- `Ctrl-t` + `Ctrl-t`: Sendet Escape-Sequenz

## Zurück zu ZMK Studio

Nach dem Debugging:

1. USB Logging in `tipper_tf.conf` deaktivieren:
   ```
   CONFIG_ZMK_USB_LOGGING=n
   ```

2. ZMK Studio wieder aktivieren:
   ```
   CONFIG_ZMK_STUDIO=y
   ```

3. Device Tree wiederherstellen:
   - `zmk,studio-rpc-uart = &studio_rpc_usb_uart;` in `chosen` hinzufügen
   - `studio_rpc_usb_uart` Node unter `zephyr_udc0` wiederherstellen
   - `usb_logging_uart` entfernen

4. Firmware neu bauen und flashen

## Alternative: Separate Config-Datei

Für schnelles Umschalten kann eine separate Config-Datei erstellt werden:

**Datei:** `keyboards/tipper_tf/tipper_tf-debug.conf`

Diese Datei enthält alle USB Logging Einstellungen. Beim Build kann dann zwischen den Configs gewechselt werden:

```bash
# Mit USB Logging
west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf -DDTC_OVERLAY_FILE=keyboards/tipper_tf/tipper_tf-debug.conf

# Ohne USB Logging (Standard)
west build -s zmk/app -b tipper_tf -- -DZMK_CONFIG=/workspaces/ZMK-tf2/keyboards/tipper_tf
```

## Weitere Ressourcen

- [ZMK USB Logging Dokumentation](https://zmk.dev/docs/development/usb-logging)
- [tio Dokumentation](https://tio.github.io/)
- [Zephyr Logging System](https://docs.zephyrproject.org/4.1.0/services/logging/index.html)
