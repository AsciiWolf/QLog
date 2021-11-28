# QLog

QLog is an Amateur Radio logging application for Linux, Windows and Mac OS. It
is based on the Qt 5 framework und uses SQLite as database backend.

QLogs aims to be as simple as possible, but to provide everything the operator expects from the log. This log is not currently focused on contests.

![Screenshot](https://foldynl.github.io/QLog/screens/qlog_main.png)

## Features

- ADIF import/export
- Rig and rotator control via Hamlib
- HamQTH callbook integration
- DX cluster integration
- **LotW**, **eQSL** and **Clublog** integration (**eQSL includes QSL pictures download**)
- **Secure Password Storage** for all services with password
- **Online** and **Offline** map
- Bandmap
- WSJT-X integration
- Station Location Profile support
- Various station statistics
- Basic Awards support
- Custom QSO Filters
- Basic Satellite support
- **NO** ads, **NO** user tracking, **NO** hidden telemetry - simply free and open-source

For more details, screenshots etc, please, see [QLog Wiki](https://github.com/foldynl/QLog/wiki)

Please, used [QLog Issues](https://github.com/foldynl/QLog/issues) for reporting any issue or open a [discussion](https://github.com/foldynl/QLog/discussions).


## Installation
### Minimum Hardware Requirements
- The recommended graphical resolution: 1920x1080
- CPU and memory: minimum requirements the same as for your OS
- Graphic Card with OpenGL support
- Serial connection if radio control is used
 
### Windows
**For users:**

Prerequisites:

- Installed [Trusted QSL](http://www.arrl.org/tqsl-download) (Optional)

Installaction packages are available for [Windows 64bit](https://github.com/foldynl/QLog/releases)

**For developers:**

Prerequisites

- Visual Studio 2015
- Installed Qt 5.12 for Windows
- Installed [qtkeychain-devel](https://github.com/frankosterfeld/qtkeychain) library and headers
- Installed [OpenSSL-devel](https://wiki.openssl.org/index.php/Binaries) libraries and headers
- Installed [HamLib-devel](https://github.com/Hamlib/Hamlib/releases/latest) libraries and headers
- All integrated in QT Creator

To be honest, It is not easy to compile it under Windows but it is possible.

### Linux

**For users:**

Prerequisites:

- Installed Trusted QSL (Optional) - `sudo apt install trustedqsl` or from [ARRL](http://www.arrl.org/tqsl-download)

Repos for Ubuntu (**.deb**) are available for amd64, arm64 and armhf platforms via [Ubuntu PPA](https://launchpad.net/~foldyna/+archive/ubuntu/qlog). Ubuntu 20.04 users can use following commands:

`sudo add-apt-repository ppa:foldyna/qlog`

`sudo apt update`

`sudo apt install qlog`

**RPM package** is planned in a future version. **Snap or Flatpak** are not planned at this moment.


**For developers:**

`sudo apt-get -y install qtbase5-dev libsqlite3-dev libhamlib++-dev libqt5charts5-dev qt5-default qttools5-dev-tools libqt5keychain1 qt5keychain-dev qtwebengine5-dev `

`git clone --recurse-submodules https://github.com/foldynl/QLog.git`

`cd  QLog`

`qmake QLog.pro`

`make`


### MacOS

TBD - Need help

## License

Copyright (C) 2020  Thomas Gatzweiler

Copyright (C) 2021  Ladislav Foldyna

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
