### VMWare | Ubuntu 15.10

This document walks you through setting up Cinder in a Ubuntu or Xubuntu 15.10 guest running under VMWare 12.0.

<br>
<br>
<br>

### Prerequisites

In a newly installed version of Ubuntu, create a `vmware-mesa.sh` with the following content.

```bash
#!/bin/sh

# File: vm-

# Builds and install kernel modules for OpenGL 3.3 Core Profile on 
# Ubuntu 15.10 running on VMWare Workstation 12 and VMWare Fusion 8. 
#
# Host OS (Linux, OS X, or Windows)  must have at least OpenGL 
# Core Profile 4.0 support. 
#
# Extracted from here: http://www.mesa3d.org/vmware-guest.html
#

sudo apt-get -y install git git-core gcc g++
sudo apt-get -y install automake libtool libpthread-stubs0-dev
sudo apt-get -y install xserver-xorg-dev x11proto-xinerama-dev libx11-xcb-dev
sudo apt-get -y install libxcb-glx0-dev libxrender-dev
sudo apt-get -y install mesa-utils xutils-dev
sudo apt-get -y build-dep libgl1-mesa-dri libxcb-glx0-dev

export TOP=$PWD
git clone git://anongit.freedesktop.org/git/mesa/mesa
git clone git://anongit.freedesktop.org/git/mesa/vmwgfx
git clone git://anongit.freedesktop.org/git/mesa/drm
git clone git://anongit.freedesktop.org/git/xorg/driver/xf86-video-vmware

export LIBDIR=/usr/lib/x86_64-linux-gnu

cd $TOP/drm
./autogen.sh --prefix=/usr --libdir=${LIBDIR}
make -j 4
sudo make install

cd $TOP/mesa
./autogen.sh --prefix=/usr --libdir=${LIBDIR} --with-gallium-drivers=svga --with-dri-drivers=swrast --enable-xa --disable-dri3 --enable-glx-tls
make -j 4
sudo make install

cd $TOP/xf86-video-vmware
./autogen.sh --prefix=/usr --libdir=${LIBDIR}
make -j 4
sudo make install

mkdir -p $TOP/vmware-mesa-backup
sudo cp /lib/modules/`uname -r`/kernel/drivers/gpu/drm/vmwgfx/vmwgfx.ko* $TOP/vmware-mesa-backup
sudo rm /lib/modules/`uname -r`/kernel/drivers/gpu/drm/vmwgfx/vmwgfx.ko*

cd $TOP/vmwgfx
make -j 4
sudo make install
sudo depmod -a

sudo update-initramfs -u

echo vmwgfx | sudo tee -a /etc/modules

# Prints out the installed location of vmwgfx.ko
find /lib/modules -name vmwgfx.ko -exec ls -l '{}' \;
```

Now run. It should take about 10-20 minutes to finish.

```bash
$ chmod +x vmware-mesa.sh
$ ./vmware-mesa.sh
```

<br>
<br>
<br>

### Building

