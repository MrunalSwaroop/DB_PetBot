# Contributing

Keep firmware changes modular. New behavior should normally be added under `src/features/<feature-name>/` with a focused interface, implementation, feature metadata, and a change note under `docs/changes/`.

For every meaningful behavior change, update the relevant entry in `CHANGELOG.md`. Update `docs/FEATURES.md` when a feature is added or its support matrix changes. Update `docs/DEVICE_MATRIX.md` when board capabilities or device configuration changes. Release and deployment records are updated when a build is published or deployed.

Use a short Conventional Commit-style message, such as:

```text
feat(led): make blink interval configurable
fix(ota): reject artifacts for another board
chore(ci): pin PlatformIO toolchain
```

Do not commit Wi-Fi credentials, API keys, firmware signing keys, or other secrets.
