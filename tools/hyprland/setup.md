# Arch + Hyprland — Desktop Setup (HyDE)

When setting up a new machine with **Arch + Hyprland**, use the **most popular HyDe config**:

- **Repo:** [HyDE-Project/HyDE](https://github.com/HyDE-Project/HyDE)
- **Formerly:** `prasanthrangan/hyprdots` (deprecated, superseded by the HyDE project)

## Install

```bash
sudo pacman -S --needed git base-devel
git clone --depth 1 https://github.com/HyDE-Project/HyDE ~/HyDE
cd ~/HyDE/Scripts
./install.sh
```

Reboot after the installer finishes, then select the **Hyprland / HyDE** session from the display manager.

## Notes

- Designed for a minimal Arch install; may work on some Arch-based distros (CachyOS, EndeavourOS, Garuda).
- Auto-detects NVIDIA and installs a matching DKMS driver.
- Heavily customized — conflicts with existing GTK/Qt theming, shell, SDDM, GRUB configs.
- Make a snapshot (Timeshift) first on BigLinux/Manjaro.

## hyprlock — disable failed-password lockout

hyprlock's password prompt uses PAM. Arch's `system-auth` loads
`pam_faillock`, which locks the account after repeated wrong passwords
(defaults: `deny = 3`, `unlock_time = 600` = 10 min). hyprlock's PAM service
(`/etc/pam.d/hyprlock`) does `auth include login`, which pulls in
`system-auth`, so it inherits the faillock stack.

To **disable the lockout entirely** (keep normal password auth):

```bash
echo 'deny = 0' | sudo tee -a /etc/security/faillock.conf
sudo faillock --reset
```

- `deny = 0` disables the faillock lockout (per Arch docs).
- PAM re-reads `faillock.conf` on every auth attempt — no reload/reboot needed.
- `faillock --reset` clears any lockout already in effect.
- To use a short lockout instead: `deny = 5` and `unlock_time = 30`.

Verify:

```bash
rg -n '^deny' /etc/security/faillock.conf   # → deny = 0
faillock                                     # empty table = no lockout
```
