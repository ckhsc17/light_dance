# light_dance

好的，以下是一段**不使用表情符號**、偏向正式與技術導向的 GitHub 倉庫描述，包含你這個「光舞系統」的**設計目的、系統架構、技術堆疊與特色**，適合放在倉庫首頁或 `README.md` 開頭：

---

## LightDance: Distributed LED Choreography System with MQTT Synchronization

This repository contains the full source code, configuration, and choreography logic for **LightDance**, a distributed light performance system designed for synchronized LED effects across multiple wearable or stationary devices. The system is intended for use in music-driven stage performances or interactive light installations.

### System Overview

The LightDance system adopts a **decentralized architecture**, where each microcontroller (e.g., Arduino) independently controls its own LED strip based on its assigned `ROLE`. A central controller (typically a laptop or Raspberry Pi) sends beat-level signals over **MQTT** to all devices. Each device then determines its own LED behavior based on the current beat and its assigned role, enabling precise coordination without requiring direct inter-device communication.

### Features

* **Role-based choreography control**
  Each device is assigned a unique `ROLE` value that determines its LED response timing and color patterns. LED effects are triggered only when the global beat matches the role's designated index in the choreography sequence.

* **MQTT-based timing synchronization**
  All devices subscribe to a shared MQTT topic (e.g., `LED_TOPIC`). The `start_music.py` script publishes beat indices in real time, synchronized with audio playback, ensuring all devices react to the same timing signals.

* **Beat-level choreography logic**
  The system supports fixed and programmable light patterns, such as sequential lighting (`1 → 2 → 3 → ...`), mirrored pairs (`1 & 7`, `2 & 6`, etc.), and custom per-beat configurations. Timing is computed based on BPM values, and per-device delay logic is used to control effect order.

* **Modular design with `ColorSet` and `BodyPart` abstraction**
  LED mappings are structured using the `BodyPart` and `LedRange` structs, which allow precise control of specific LED segments (e.g., arms, legs, collar). This allows color sets to be defined independently of physical layout.

* **Music integration**
  The repository includes several `.m4a` and `.mp3` files used for synchronized light performances. The music and beat mapping logic is handled via the Python MQTT script and manual annotation of choreography timing.

* **Support for test mode and iteration**
  Multiple subfolders (`sketch_lightdance_1`, `_test`, `All`, `What_Makes_You_Beautiful`, etc.) contain different versions of the Arduino sketches corresponding to different songs and choreography versions, facilitating modular updates and debugging.

### File Highlights

* `start_music.py`: Python script to send MQTT messages in sync with local audio playback.
* `sketch_lightdance_1/`: Core Arduino code for LED control, role assignment, beat-based logic.
* `Light_Dance*.m4a`: Audio tracks used during actual performances.
* `LightDance.ino`: Main sketch (inside subfolders), containing color logic, beat timing, and part mapping.

### Intended Applications

This project is suitable for:

* Group performances with distributed LED suits
* Real-time synchronized light shows
* Educational demonstrations on IoT, MQTT, and embedded choreography systems
