# Testing

Baseline host: Linux x86-64 with the project development kit extracted externally.

Set `GRINDUNGEONIA_DEVKIT` to the kit root, then:

```sh
tools/build.sh
tools/capture.sh --frames 120 --output captures/idle.png
tools/capture.sh --frames 120 --sequence verification/g00_input.json --output captures/input.png
```

G0.0 acceptance: compile `Grindungeonia.gba`; boot under bundled mGBA core; capture 240x160 PNG; scripted input visibly changes the rendered frame.
