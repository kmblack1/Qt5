# 1更新Ubuntu软件
```bash
sudo apt-get update
sudo apt-get -y dist-upgrade
```

# 2.移除旧内核
```bash
uname -a #查看当前系统使用的内核.
sudo dpkg --get-selections|grep linux
sudo apt-get autoremove -y --purge
sudo reboot
```

# 3.修改时区和校准时间
```bash
sudo dpkg-reconfigure tzdata
sudo apt-get install ntpdate // 安装时间同步工具
sudo ntpdate cn.pool.ntp.org // 与网络服务器同步时间
timedatectl status
date // 查看时间是否已同步
```



# 4.安装编译套件和常用工具
```bash
#查找软件包
sudo apt-cache search open-vm-tools
#
sudo apt-get -y install build-essential libtool automake cmake unzip clang git wget open-vm-tools

sudo apt-get -y install firefox firefox-locale-zh-hans
sudo apt-cache search libxcb
sudo apt-get install -y libxcb-xinerama0
```

# 5.安装中文支持
```bash
#查看语言支持
locale -a
#安装安装中文支持
sudo locale-gen zh_CN.UTF-8
#安装中文字体
sudo apt-get -y install fonts-wqy-zenhei fonts-wqy-microhei  xfonts-wqy
#设置操作系统语言后重启
sudo reboot
```

# 6.安装Visual Studio Code
[下载](https://code.visualstudio.com/Download)
```bash
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
rm -f packages.microsoft.gpg
sudo apt install apt-transport-https
sudo apt update
sudo apt install code # or code-insiders
```

# 6.安装Qt5
如果没有注册需要先注册

[下载](https://www.qt.io/download)
```bash
chmod +x ~/Downloads/qt-unified-linux-x64-4.3.0-online.run
~/Downloads/qt-unified-linux-x64-4.3.0-online.run
```

# 7.下载安装Clion
如果没有注册需要先注册

[下载](https://www.jetbrains.com/clion/)
```bash
tar -xf ~/Downloads/CLion-2021.3.3.tar.gz
mv /home/kmblack/Downloads/clion-2021.3.3 /home/kmblack/clion-2021.3.3
cd /home/kmblack/clion-2021.3.3
~/clion-2021.3.3/bin/clion.sh
```


# 8.下载安装google chrome
需要科学上网

[下载](https://www.google.com/chrome/)
```bash
sudo dpkg -i ~/Downloads/google-chrome-stable_current_amd64.deb
```

# 9.清除并自动关联依赖软件
```bash
sudo apt-get -y autoclean &&\
sudo apt-get -y clean &&\
sudo apt-get -y autoremove --purge &&\
sudo apt-get -y remove --purge &&\
sudo apt-get -f install
```
