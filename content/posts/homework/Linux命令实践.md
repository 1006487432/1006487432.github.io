---
title: Linux命令实践
subtitle:
date: 2024-09-10T11:12:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords:
license:
comment: false
weight: 0
tags:
  - 
categories:
  - homework
hiddenFromHomePage: false
hiddenFromSearch: false
hiddenFromRss: false
hiddenFromRelated: false
summary:
resources:
  - name: featured-image
    src: featured-image.jpg
  - name: featured-image-preview
    src: featured-image-preview.jpg
toc: true
math: false
lightgallery: false
password:
message:
repost:
  enable: true
  url:

# See details front matter: https://fixit.lruihao.cn/documentation/content-management/introduction/#front-matter
---

<!--more-->


# 课上测试

## 作业题目：Linux命令实践

### 学习Linux核心命令

-  ls
-  who
-  pwd
-  cd
-  man
-  whereis
-  which
-  find
-  locate
-  grep

### 作业要求（9‘）

- 参考课件，针对上面核心命令重复老师的演示内容（3’）
- 选择自己习惯的 AI 工具， 针对上面核心命令，让 AI 给自己生成至少例子，然后自己进行验证，总结（3’）
- 让 AI工具推荐一些重要命令，然后选择自己认为会高频应用的至少 3个命令（重点推荐 echo，od，sort，bc，ls）进行自主深入学习，每个命令不少于 5 个例子，提交验证，实践过程和总结（3’）

## 实践

### 重复老师演示得内容

- ls

  - ~~~shell
    $ ls
    GmSSL-master  py  snap
    ~~~

  - ~~~ shell
    $ ls .
    GmSSL-master  py  snap
    ~~~

  - ~~~ shell
    $ ls -a
    .              .bash_logout  .config     .java     .motd_shown       .sage                      GmSSL-master
    ..             .bashrc       .gdbinit    .lesshst  .profile          .sudo_as_admin_successful  py
    .bash_history  .cache        .gitconfig  .local    .pycharm_helpers  .viminfo                   snap
    ~~~

  - ~~~ shell
    $ ls -l
    total 12
    drwxr-xr-x 9 zhanhe zhanhe 4096 Sep  4 10:08 GmSSL-master
    drwxr-xr-x 3 zhanhe zhanhe 4096 Aug 22 14:05 py
    drwx------ 3 zhanhe zhanhe 4096 Sep 10 11:01 snap
    ~~~

  - ~~~ shell
    $ ls -R
    .:
    GmSSL-master  py  snap
    
    ./GmSSL-master:
    CMakeLists.txt  INSTALL.md  LICENSE  README.md  build  cmake  include  src  tests  tools
    内容过多，仅复制一小段
    ~~~

  - ~~~ shell
    $ ls -lh
    total 12K
    drwxr-xr-x 9 zhanhe zhanhe 4.0K Sep  4 10:08 GmSSL-master
    drwxr-xr-x 3 zhanhe zhanhe 4.0K Aug 22 14:05 py
    drwx------ 3 zhanhe zhanhe 4.0K Sep 10 11:01 snap
    ~~~

- who

  - ~~~ shell
    $ who
    zhanhe   pts/1        2024-09-10 11:04
    ~~~

  - ~~~ shell
    $ whoami
    zhanhe
    ~~~

  - ~~~ shell
    $ who -a
               system boot  2024-09-10 11:04
               run-level 5  2024-09-10 11:04
    LOGIN      tty1         2024-09-10 11:04               292 id=tty1
    LOGIN      console      2024-09-10 11:04               285 id=cons
    zhanhe   - pts/1        2024-09-10 11:04 00:15         427
    ~~~

- pwd

  - ~~~ shell
    $ pwd
    /home/zhanhe
    ~~~

- cd 

  - ~~~ shell
    ~$ cd /
    /$ pwd
    /
    ~~~

  - ~~~ shell
    /$ cd /home/zhanhe
    ~$ pwd
    /home/zhanhe
    ~~~

  - ~~~ shell
    /$ cd ~
    ~$ pwd
    /home/zhanhe
    ~~~

  - ~~~ shell
    ~/GmSSL-master$ cd .
    ~/GmSSL-master$ pwd
    /home/zhanhe/GmSSL-master
    ~~~

  - ~~~ shell
    ~/GmSSL-master$ cd ..
    ~$ pwd
    /home/zhanhe
    ~~~

  - ~~~ shell
    ~$ cd -
    /home/zhanhe/GmSSL-master
    ~/GmSSL-master$
    ~~~

- man

  - ~~~ shell
    MAN(1)                                               Manual pager utils                                               MAN(1)
    NAME
           man - an interface to the system reference manuals
    ~~~

  - ~~~ shell
    PRINTF(1)                                               User Commands                                              PRINTF(1)
    NAME
           printf - format and print data
    ~~~

  - ~~~ shell 
    PRINTF(3)                                         Linux Programmer's Manual                                        PRINTF(3)
    NAME
           printf, fprintf, dprintf, sprintf, snprintf, vprintf, vfprintf, vdprintf, vsprintf, vsnprintf - formatted output con‐
           version
    ~~~

  - ~~~ shell
    $ man -k printf
    asprintf (3)         - print to allocated string
    dprintf (3)          - formatted output conversion
    fmtcheck (3bsd)      - sanitizes user-supplied printf(3)-style format string
    fprintf (3)          - formatted output conversion
    fwprintf (3)         - formatted wide-character output conversion
    printf (1)           - format and print data
    printf (3)           - formatted output conversion
    set_matchpathcon_printf (3) - set flags controlling the operation of matchpathcon or matchpathcon_index and configure the beh...
    snprintf (3)         - formatted output conversion
    sprintf (3)          - formatted output conversion
    swprintf (3)         - formatted wide-character output conversion
    vasprintf (3)        - print to allocated string
    vdprintf (3)         - formatted output conversion
    vfprintf (3)         - formatted output conversion
    vfwprintf (3)        - formatted wide-character output conversion
    vprintf (3)          - formatted output conversion
    vsnprintf (3)        - formatted output conversion
    vsprintf (3)         - formatted output conversion
    vswprintf (3)        - formatted wide-character output conversion
    vwprintf (3)         - formatted wide-character output conversion
    wprintf (3)          - formatted wide-character output conversion
    XtAsprintf (3)       - memory management functions
    ~~~

  - ~~~ shell
    $ man -f printf
    printf (1)           - format and print data
    printf (3)           - formatted output conversion
    ~~~

  - ~~~ shell
    $ man -k printf | grep 3
    asprintf (3)         - print to allocated string
    dprintf (3)          - formatted output conversion
    fmtcheck (3bsd)      - sanitizes user-supplied printf(3)-style format string
    fprintf (3)          - formatted output conversion
    fwprintf (3)         - formatted wide-character output conversion
    printf (3)           - formatted output conversion
    set_matchpathcon_printf (3) - set flags controlling the operation of matchpathcon or matchpathcon_index and configure the beh...
    snprintf (3)         - formatted output conversion
    sprintf (3)          - formatted output conversion
    swprintf (3)         - formatted wide-character output conversion
    vasprintf (3)        - print to allocated string
    vdprintf (3)         - formatted output conversion
    vfprintf (3)         - formatted output conversion
    vfwprintf (3)        - formatted wide-character output conversion
    vprintf (3)          - formatted output conversion
    vsnprintf (3)        - formatted output conversion
    vsprintf (3)         - formatted output conversion
    vswprintf (3)        - formatted wide-character output conversion
    vwprintf (3)         - formatted wide-character output conversion
    wprintf (3)          - formatted wide-character output conversion
    XtAsprintf (3)       - memory management functions
    ~~~

- whereis

  - ~~~ shell
    $ whereis ls
    ls: /usr/bin/ls /usr/share/man/man1/ls.1.gz
    ~~~

- which

  - ~~~ shell
    $ which ls
    /usr/bin/ls
    ~~~

- find

  - ~~~ shell
    $ find -name flag
    ./home/zhanhe/.local/lib/python3.10/site-packages/pwnlib/flag
    find: ‘./etc/polkit-1/localauthority’: Permission denied
    find: ‘./etc/ssl/private’: Permission denied
    ./flag
    find: ‘./root’: Permission denied
    find: ‘./mnt/e/$RECYCLE.BIN/S-1-5-21-1401408247-2291080922-2548902397-1001’: Permission denied
    find: ‘./mnt/e/$RECYCLE.BIN/S-1-5-21-1401408247-2291080922-2548902397-1002’: Permission denied
    ~~~

- locate

  - ~~~ shell
    $ locate hello.c
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/c/groovy/src/hello/c/hello.c
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/cpp/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/cpp-exe/groovy/src/main/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/cpp-lib/groovy/src/main/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/custom-layout/groovy/src/source/hello.c
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/flavors/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/multi-project/groovy/lib/src/main/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/pre-compiled-headers/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/variants/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/visual-studio/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/documentation/docs/src/snippets/native-binaries/windows-resources/groovy/src/hello/cpp/hello.cpp
    /mnt/c/Users/He-Zh/.gradle/caches/transforms-4/435be38f8324990cec484e03044db2a0/transformed/unzipped-distribution/gradle-8.6/platforms/software/build-init/src/main/resources/org/gradle/buildinit/tasks/templates/cpplibrary/hello.cpp.template
    /mnt/c/Users/He-Zh/Desktop/Understanding UnixLinux Programming/chapters/ch01/class/classcode/hello.c
    /mnt/c/Users/He-Zh/Desktop/Understanding UnixLinux Programming/chapters/ch06/class/classcode/hello.c
    /mnt/c/Users/He-Zh/Desktop/Understanding UnixLinux Programming/chapters/ch12/class/classcode/hello.cgi
    /mnt/c/Users/He-Zh/Desktop/Understanding UnixLinux Programming/projects/wsng/public_html/wsng/dir2/hello.c
    /mnt/c/Users/He-Zh/Desktop/Understanding UnixLinux Programming/projects/wsng/public_html/wsng/dir2/hello.cgi
    /mnt/d/javaworkplace/hello/bin/hello/hello.class
    /mnt/d/javaworkplace/hello/src/hello/hello.class
    /mnt/d/metasploit-framework/embedded/lib/ruby/gems/3.1.0/gems/mini_portile2-2.8.6/test/assets/test-cmake-1.0/hello.c
    /mnt/e/Qt/Examples/Qt-6.7.1/qmake/tutorial/hello.cpp
    /mnt/e/go/src/debug/elf/testdata/hello.c
    /mnt/e/go/src/debug/macho/testdata/hello.c
    /mnt/e/go/src/debug/pe/testdata/hello.c
    /mnt/e/go/src/debug/plan9obj/testdata/hello.c
    /mnt/e/go/src/internal/xcoff/testdata/hello.c
    /mnt/e/go/src/internal/xcoff/testdata/printhello.c
    /usr/share/doc/fltk1.3-doc/examples/hello.cxx
    ~~~

- grep

  - ~~~ shell
    $ grep -nr setup.sh ~
    grep: /home/zhanhe/.cache/JetBrains/RemoteDev/dist/5e55a3f40833c_RustRover-2024.1.5/plugins/clouds-docker-impl/lib/clouds-docker-impl.jar: binary file matches
    grep: /home/zhanhe/.cache/JetBrains/RemoteDev/dist/5e55a3f40833c_RustRover-2024.1.5/plugins/remoteRun/lib/remoteRun.jar: binary file matches
    
    /home/zhanhe/.bash_history:63:./setup.sh
    /home/zhanhe/.bash_history:65:./setup.sh
    /home/zhanhe/.bash_history:70:./setup.sh
    /home/zhanhe/.bash_history:89:./setup.sh
    /home/zhanhe/.bash_history:156:./setup.sh
    /home/zhanhe/.bash_history:181:./setup.sh
    /home/zhanhe/.bash_history:219:./setup.sh
    /home/zhanhe/.bash_history:220:sudo ./setup.sh
    /home/zhanhe/.bash_history:224:./setup.sh
    /home/zhanhe/.bash_history:236:./setup.sh
    /home/zhanhe/.bash_history:261:./setup.sh
    /home/zhanhe/.bash_history:263:./setup.sh
    /home/zhanhe/.bash_history:269:./setup.sh
    /home/zhanhe/.bash_history:271:./setup.sh
    /home/zhanhe/.pycharm_helpers/typeshed/stubs/setuptools/setuptools/command/build_ext.pyi:25:    def setup_shlib_compiler(self) -> None: ...
    /home/zhanhe/.local/pwntools-doc/TESTING.md:11:bash travis/ssh_setup.sh
    /home/zhanhe/.local/share/virtualenv/wheel/3.10/image/1/CopyPipInstall/setuptools-68.2.0-py3-none-any/setuptools/command/build_ext.py:186:            self.setup_shlib_compiler()
    /home/zhanhe/.local/share/virtualenv/wheel/3.10/image/1/CopyPipInstall/setuptools-68.2.0-py3-none-any/setuptools/command/build_ext.py:211:    def setup_shlib_compiler(self):
    grep: /home/zhanhe/.local/share/pypoetry/venv/lib/python3.10/site-packages/setuptools/command/__pycache__/build_ext.cpython-310.pyc: binary file matches
    /home/zhanhe/.local/share/pypoetry/venv/lib/python3.10/site-packages/setuptools/command/build_ext.py:142:            self.setup_shlib_compiler()
    /home/zhanhe/.local/share/pypoetry/venv/lib/python3.10/site-packages/setuptools/command/build_ext.py:164:    def setup_shlib_compiler(self):
    grep: /home/zhanhe/.local/share/pypoetry/venv.save/lib/python3.10/site-packages/setuptools/command/__pycache__/build_ext.cpython-310.pyc: binary file matches
    /home/zhanhe/.local/share/pypoetry/venv.save/lib/python3.10/site-packages/setuptools/command/build_ext.py:142:
      self.setup_shlib_compiler()
    /home/zhanhe/.local/share/pypoetry/venv.save/lib/python3.10/site-packages/setuptools/command/build_ext.py:164:    def setup_shlib_compiler(self):
    /home/zhanhe/py/pythonProject1/.venv/lib/python3.10/site-packages/setuptools/command/build_ext.py:186:            self.setup_shlib_compiler()
    /home/zhanhe/py/pythonProject1/.venv/lib/python3.10/site-packages/setuptools/command/build_ext.py:211:    def setup_shlib_compiler(self):
    ~~~

### AI-常用指令
#### AI回答
当然！以下是这些常用Linux命令的解释和使用示例：
##### 1. **`ls`** - 列出目录内容
`ls` 命令用于列出当前目录或指定目录中的文件和子目录。

- **示例 1:** 列出当前目录下的所有文件和目录
  ```bash
  ls
  ```
- **示例 2:** 列出详细信息（包括权限、所有者、大小、修改时间等）
  ```bash
  ls -l
  ```
- **示例 3:** 列出包含隐藏文件的所有文件和目录
  ```bash
  ls -a
  ```

##### 2. **`who`** - 显示当前登录的用户
`who` 命令用于显示当前登录到系统的所有用户信息。

- **示例 1:** 显示当前登录的用户列表
  ```bash
  who
  ```
- **示例 2:** 显示用户的登录时间和TTY信息
  ```bash
  who -u
  ```

##### 3. **`pwd`** - 显示当前工作目录
`pwd` 命令用于显示当前所在的工作目录的绝对路径。

- **示例 1:** 显示当前目录的路径
  ```bash
  pwd
  ```

##### 4. **`cd`** - 更改目录
`cd` 命令用于在文件系统中更改当前工作目录。

- **示例 1:** 切换到指定目录
  ```bash
  cd /home/user/Documents
  ```
- **示例 2:** 返回到上一级目录
  ```bash
  cd ..
  ```
- **示例 3:** 切换到用户的主目录
  ```bash
  cd ~
  ```

##### 5. **`man`** - 显示手册页
`man` 命令用于显示指定命令的手册页，可以查看命令的详细信息和使用方式。

- **示例 1:** 查看 `ls` 命令的手册页
  ```bash
  man ls
  ```
- **示例 2:** 查看 `man` 命令的手册页
  ```bash
  man man
  ```

##### 6. **`whereis`** - 查找二进制、源代码和手册页文件
`whereis` 命令用于定位二进制文件、源代码文件和手册页文件的路径。

- **示例 1:** 查找 `ls` 命令的路径
  ```bash
  whereis ls
  ```
- **示例 2:** 查找 `bash` 命令的所有相关文件
  
  ```bash
  whereis bash
  ```

##### 7. **`which`** - 显示命令的可执行文件路径
`which` 命令用于显示指定命令的可执行文件所在路径。

- **示例 1:** 显示 `python` 命令的路径
  ```bash
  which python
  ```
- **示例 2:** 显示 `ls` 命令的路径
  ```bash
  which ls
  ```

##### 8. **`find`** - 查找文件
`find` 命令用于查找目录树中的文件和目录。

- **示例 1:** 在当前目录及其子目录中查找名为 `file.txt` 的文件
  
  ```bash
  find . -name "file.txt"
  ```
- **示例 2:** 查找大小超过 10MB 的文件
  ```bash
  find / -size +10M
  ```

##### 9. **`locate`** - 查找文件
`locate` 命令通过查询预先构建的数据库快速查找文件。

- **示例 1:** 查找名为 `passwd` 的文件
  ```bash
  locate passwd
  ```
- **示例 2:** 查找包含 `conf` 的所有文件
  ```bash
  locate conf
  ```

##### 10. **`grep`** - 搜索文本
`grep` 命令用于在文件或输入中搜索匹配的文本模式。

- **示例 1:** 在文件 `logfile.txt` 中查找包含 `error` 的行
  ```bash
  grep "error" logfile.txt
  ```
- **示例 2:** 查找当前目录下所有 `.txt` 文件中包含 `example` 的行
  ```bash
  grep "example" *.txt
  ```
- **示例 3:** 搜索时忽略大小写
  
  ```bash
  grep -i "example" logfile.txt
  ```

##### 总结

这些命令是Linux系统中常用的基本命令，掌握这些命令将帮助你高效地管理和操作系统。

#### 实践

##### grep

~~~ shell
$ ls
GmSSL-master  flag  py  snap
$ cat flag
FLAG
flag
flag
FLAG
$ grep "flag" flag
flag
flag
$ grep -i "flag" flag
FLAG
flag
flag
FLAG
$ grep -i "flag" *
grep: GmSSL-master: Is a directory
flag:FLAG
flag:flag
flag:flag
flag:FLAG
grep: py: Is a directory
grep: snap: Is a directory
~~~

##### find

~~~ shell
$ find / -size +1024M
find: ‘/etc/polkit-1/localauthority’: Permission denied
find: ‘/etc/ssl/private’: Permission denied
find: ‘/root’: Permission denied
find: ‘/mnt/e/$RECYCLE.BIN/S-1-5-21-1401408247-2291080922-2548902397-1001’: Permission denied
find: ‘/mnt/e/$RECYCLE.BIN/S-1-5-21-1401408247-2291080922-2548902397-1002’: Permission denied
/mnt/e/20240827_113100.mp4
/mnt/e/20240827_165004.mp4
/mnt/e/20240908_101433.mp4
/mnt/e/BaiduNetdiskDownload/MATLAB R2024a(64bit)/Setup/archives/win64/3p/cuda_win64_1700448735.enc
/mnt/e/BaiduNetdiskDownload/MATLAB R2024a(64bit).zip
/mnt/e/kali-linux-2024.2-vmware-amd64.7z
/mnt/e/kali-linux-2024.2-vmware-amd64.vmwarevm/kali-linux-2024.2-vmware-amd64-s001.vmdk
/mnt/e/kali-linux-2024.2-vmware-amd64.vmwarevm/kali-linux-2024.2-vmware-amd64-s002.vmdk
/mnt/e/kali-linux-2024.2-vmware-amd64.vmwarevm/kali-linux-2024.2-vmware-amd64-s035.vmdk
......
~~~



### AI推荐重要命令
#### AI回答	
当然可以！以下是一些在 Linux 中非常重要和常用的指令，涵盖系统管理、文件操作、网络管理等多个方面：

##### 1. **`ls`**
   - **用途**: 列出目录内容。
   - **重要性**: 这是文件管理的基础命令，用于查看目录下的文件和文件夹。

##### 2. **`cd`**
   - **用途**: 更改当前工作目录。
   - **重要性**: 每次在文件系统中导航时都需要使用这个命令。

##### 3. **`pwd`**
   - **用途**: 显示当前工作目录的绝对路径。
   - **重要性**: 当你需要确认自己当前所在的目录时，这个命令非常有用。

##### 4. **`cp`**
   - **用途**: 复制文件或目录。
   - **重要性**: 用于备份文件或在不同目录之间复制文件。

##### 5. **`mv`**
   - **用途**: 移动文件或重命名文件。
   - **重要性**: 用于组织文件、将文件从一个位置移动到另一个位置，或重命名文件。

##### 6. **`rm`**
   - **用途**: 删除文件或目录。
   - **重要性**: 在清理不再需要的文件或目录时，使用这个命令。

##### 7. **`chmod`**
   - **用途**: 更改文件或目录的权限。
   - **重要性**: 这个命令是管理文件权限、确保安全性的重要工具。

##### 8. **`chown`**
   - **用途**: 更改文件或目录的所有者和组。
   - **重要性**: 在管理多用户系统时，确保正确的所有权设置至关重要。

##### 9. **`tar`**
   - **用途**: 归档文件（通常与 `gzip` 结合使用）。
   - **重要性**: 在备份、压缩和传输文件时非常有用。

##### 10. **`ps`**
- **用途**: 显示当前运行的进程。
- **重要性**: 用于监视和管理系统上的进程，了解正在运行的程序。

##### 11. **`top`**
- **用途**: 实时显示系统进程和资源使用情况。
- **重要性**: 监视系统性能，特别是在诊断性能问题时。

##### 12. **`kill`**
- **用途**: 终止进程。
- **重要性**: 当进程挂起或消耗大量资源时，可以使用它来强制终止进程。

##### 13. **`df`**
- **用途**: 显示文件系统磁盘空间使用情况。
- **重要性**: 检查磁盘使用情况，防止磁盘空间不足。

##### 14. **`du`**
- **用途**: 显示目录或文件的磁盘使用量。
- **重要性**: 了解哪个目录或文件占用了大量磁盘空间。

##### 15. **`ssh`**
- **用途**: 通过网络远程登录到另一台机器。
- **重要性**: 管理和控制远程服务器的基本工具。

##### 16. **`scp`**
- **用途**: 通过 SSH 安全地复制文件。
- **重要性**: 在远程机器之间传输文件时，非常有用。

##### 17. **`wget`**
- **用途**: 从网络下载文件。
- **重要性**: 自动化下载任务、获取文件的实用工具。

##### 18. **`curl`**
- **用途**: 使用 URL 语法传输数据。
- **重要性**: 用于测试 API 接口、下载文件或检查网络资源。

##### 19. **`iptables`**
- **用途**: 配置 Linux 内核的网络包过滤规则。
- **重要性**: 管理和配置防火墙，确保系统的网络安全。

##### 20. **`systemctl`**
- **用途**: 控制 systemd 系统和服务管理器。
- **重要性**: 管理系统服务、启动和停止服务、查看系统状态等。

##### 21. **`crontab`**
- **用途**: 定时任务调度。
- **重要性**: 自动化任务执行，例如定期备份、系统清理。

##### 22. **`grep`**
- **用途**: 搜索文本中的特定模式。
- **重要性**: 快速查找日志文件或其他文本文件中的特定内容。

##### 23. **`find`**
- **用途**: 查找文件或目录。
- **重要性**: 在复杂的文件系统中查找文件时非常有用。

##### 24. **`alias`**
- **用途**: 为命令创建别名。
- **重要性**: 简化常用命令，节省输入时间。

##### 25. **`echo`**
- **用途**: 显示一段文本或变量的值。

- **重要性**: 调试脚本时，经常用于输出信息。

总结：掌握这些命令将极大地提升你在Linux系统上的工作效率和管理能力。
#### 实践

##### echo

~~~ shell
$ echo "123gsgdhdhFGH"
123gsgdhdhFGH

#echo重定向
$ echo "This text goes to a file" >> file.txt
$ cat file.txt
This text goes to a file

$ echo *
GmSSL-master file.txt flag py snap

#清空文件
$ echo > file.txt
$ cat file.txt

#以颜色显示 echo 命令输出
$ echo -e "\033[31m这是红色"
这是红色

#查看命令在不运行的情况下会执行什么操作
$ echo rm -R *
rm -R GmSSL-master file.txt flag py snap

~~~

##### tar

~~~ shell
1、创建归档文件：将文件 file1、file2 和 directory 打包到一个名为 archive.tar 的归档文件中。
$ tar -cvf flag.tar flag flag1 flag2
flag
flag1
flag2
$ ls
GmSSL-master  file.txt  flag  flag.tar  flag1  flag2  py  snap
2、解压归档文件：解压名为 archive.tar 的归档文件，还原其中包含的文件和目录。
$tar -xvf flag.tar
flag
flag1
flag2
3、列出归档文件中的内容：列出名为 archive.tar 的归档文件中包含的所有文件和目录。
$ tar -tvf flag.tar
-rw-r--r-- zhanhe/zhanhe    20 2024-09-10 12:25 flag
-rw-r--r-- zhanhe/zhanhe    17 2024-09-10 17:55 flag1
-rw-r--r-- zhanhe/zhanhe    23 2024-09-10 17:56 flag2
4、追加文件到已存在的归档中：将名为 newfile 的文件添加到已存在的名为 archive.tar 的归档文件中。
$ tar -rvf flag.tar file.txt
file.txt
$ tar -tvf flag.tar
-rw-r--r-- zhanhe/zhanhe    20 2024-09-10 12:25 flag
-rw-r--r-- zhanhe/zhanhe    17 2024-09-10 17:55 flag1
-rw-r--r-- zhanhe/zhanhe    23 2024-09-10 17:56 flag2
-rw-r--r-- zhanhe/zhanhe     1 2024-09-10 17:51 file.txt
6、创建一个经过 gzip 压缩的归档文件：打包 directory 目录下的所有文件和子目录，并使用 gzip 压缩，生成名为 archive.tar.gz 的归档文件。
$ tar -zcvf archive.tar.gz test
test/
test/flag1
test/flag2
$ ls
GmSSL-master  archive.tar.gz  file.txt  flag  flag.tar  py  snap  test
~~~

##### alias

~~~ shell
1.创建一个简单的alias
$ alias cf='cat /flag'
$ cf
flag{th1s_1s_n2t_f1ag}
2.创建一个包含选项的alias
$ alias la='ls -a'
$ la
.              .bash_logout  .config     .java     .motd_shown       .sage                      GmSSL-master    flag      snap
..             .bashrc       .gdbinit    .lesshst  .profile          .sudo_as_admin_successful  archive.tar.gz  flag.tar  test
.bash_history  .cache        .gitconfig  .local    .pycharm_helpers  .viminfo                   file.txt        py
3.创建一个包含多个命令的alias
$ alias update='sudo apt update && sudo apt upgrade'
$ update
4.查看所有的alias
$ alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias cf='cat /flag'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'
5.删除一个alias
$ unalias cf
$ alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'

~~~

### 总结

本次实践从重复老师上课教学内容开始到借助AI自主学习新的指令。显然，通过AI工具进一步扩展学习，进一步巩固所学知识，在平时学习中也要进一步掌握结合AI的能力，让AI辅助学习，减少重复而琐碎的行为，让注意力更加聚焦在关键的知识点。


## 作业提交要求 (1')

0. 记录实践过程和 AI 问答过程，尽量不要截图，给出文本内容
1. (选做)推荐所有作业托管到 [gitee](https://gitee.com/)或 [github](https://github.com/) 上
2. (必做)提交作业 markdown文档，命名为“学号-姓名-作业题目.md”
3. (必做)提交作业 markdown文档转成的 PDF 文件，命名为“学号-姓名-作业题目.pdf”
