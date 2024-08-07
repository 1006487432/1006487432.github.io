---
title: Rust01——Cargo
subtitle:
date: 2024-07-15T13:21:56+08:00
draft: false
author:
  name: 瞻鹤
  link:
  email: he-zhan@outlook.com
  avatar: /images/avatar.jpg
description:
keywords: Rust
license:
comment: false
weight: 0
tags:
  - 语言
categories:
  - Rust
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

## Cargo

### 使用Cargo创建项目
使用命令cargo new [项目名]创建项目
### 使用Cargo编译/运行项目

两种方式：

1. cargo run 默认是debug模式，可以添加参数--release增强代码性能

2. cargo build后./target/debug/项目名，同样可以添加参数--release

使用cargo check可以快速检查代码有没有编译错误


### 项目配置、依赖管理

`Cargo.toml` 和 `Cargo.lock` 是 `cargo` 的核心文件，它的所有活动均基于此二者。

- `Cargo.toml` 是 `cargo` 特有的**项目数据描述文件**。它存储了项目的所有元配置信息。

  - `package` 中记录了项目的描述信息

~~~ 
[package]
name = "world_hello" //项目名
version = "0.1.0" //当前版本
edition = "2021" //Rust大版本
~~~
  - dependencies则是管理项目依赖项
~~~
[dependencies] 
//三种依赖写法
rand = "0.3"
hammer = { version = "0.5.0"} //基于 Rust 官方仓库 crates.io，通过版本说明来描述
color = { git = "https://github.com/bjz/color-rs" } //基于项目源代码的 git 仓库地址，通过 URL 来描述
geometry = { path = "crates/geometry" } //基于本地项目的绝对路径或者相对路径，通过类 Unix 模式的路径来描述
~~~
- `Cargo.lock` 文件是 `cargo` 工具根据同一项目的 `toml` 文件生成的**项目依赖详细清单**。

  
