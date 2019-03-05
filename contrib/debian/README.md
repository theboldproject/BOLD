
Debian
====================
This directory contains files used to package boldd/bold-qt
for Debian-based Linux systems. If you compile boldd/bold-qt yourself, there are some useful files here.

## bold: URI support ##


bold-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bold-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your boldqt binary to `/usr/bin`
and the `../../share/pixmaps/bold128.png` to `/usr/share/pixmaps`

bold-qt.protocol (KDE)

