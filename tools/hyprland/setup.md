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
