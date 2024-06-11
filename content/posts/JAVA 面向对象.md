---
title: JAVA面向对象
subtitle:
date: 2024-06-11T13:21:56+08:00
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
  - JAVA
categories:
  - 语言
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

# 【从0开始学JAVA】 类个，我的对象在哪里？

由于本人是从C开始学习的编程菜鸟，虽然接触过一点cpp(对现在的我来说也许只是c + stl库？只是为了写算法题方便一些…)，所以我打算先学JAVA的特点和思想————面向对象编程。 （至于安装JAVA可以看我*[兄弟的博客](https://blog.csdn.net/CHTXRT/article/details/128699818?spm=1001.2014.3001.5502)*)

## 类个，总而言之，先给自己NEW一个对象吧

**面向对象**

```
面向对象(Object Oriented)是软件开发方法，一种编程范式。面向对象的概念和应用已超越了程序设计和软件开发，扩展到如数据库系统、交互式界面、应用结构、应用平台、分布式系统、网络管理结构、CAD技术、人工智能等领域。面向对象是一种对现实世界理解和抽象的方法，是计算机编程技术发展到一定阶段后的产物。
面向对象是相对于面向过程来讲的，面向对象方法，把相关的数据和方法组织为一个整体来看待，从更高的层次来进行系统建模，更贴近事物的自然运行模式。
```

————来自*[百度百科](https://baike.baidu.com/item/面向对象/2262089);

- 面向对象有三大基本特征：
  - 封装
  - 继承
  - 多态
- 面向对象的编程思想就是把事物看作一个整体，从事物的特征（属性）和行为（方法）两个方面进行描述。
- 面向对象是找对象、创建对象、使用对象、维护对象的关系的过程

**类 和 对象**是什么？

```
抛开对象不谈，我还是有对象的。
```

**类(Class)** 是具有相同特性（数据元素）和行为（功能）的对象的抽象。

- 定义类：就是定义**类的成员**，包括**成员变量**和**成员方法**
- 类的成员:
  - 成员属性：对象事物的属性；
  - 成员方法：对象事物的方法(捏造对象的方法，处理对象行为的方法等等)

该类对象中每一个对象都具有类的成员属性，都可以使用类的成员方法。 有点类似C语言中的结构体，成员属性就是结构体中函数的变量，成员方法就是结构体中包含的函数，而每一个对象都是一个结构体。

```java
public class 类名{
    //成员变量
    //成员方法
} 
struct human
{
    int age；//成员变量
    int (*)sleep()//成员方法
}
```

**对象(Object)** 的含义是指具体的某一个事物，即在现实生活中能够看得见摸得着的事物。 在JAVA这类静态语言中，**类**是**对象**的抽象，**对象**是**类**的实例化。

- 创建对象

  ```
    类名 对象名 = new 类名()
  ```

- 调用对象

  ```
    对象名.成员变量
    对象名.方法(参数列表)
  ```

面向对象的编程方法，首先我们要找到对象，思考对象具有什么属性，然后创建一个对象。

```java
public class human {
    int age;
    String name;

    public human() {
        // 没有参数的构造方法
        // 构造对象的方法，方法名与类名要相同
        name = "李华";
        age = 18;
    }// 构造一个名为李华，年龄为18岁的对象

    public human(String human_name, int human_age) {
        // 有参数的构造方法
        this.name = human_name;
        this.age = human_age;
        // this代表它所在方法所属对象的引用。哪个对象调用的this所在的方法，this就代表哪个对象。当然this还有其他作用
    }// 构造一个名为human_name,年龄为human_age的对象

    /*
     * public huamn(){
     * this("李华",18);
     * //this在构造方法第一行时且带有参数列表，则代表引用了该类下其他的捏造方法(根据参数列表选择)；
     * }
     */

    public void sleep(int time) {
        System.out.println(this.name + "睡了" + time + "小时");
    }

    public static class new_human extends human {// 子类继承父类 静态的main不能调用动态类中的方法，所以要在类前加static才能在main中调用这个类，构造子类的对象
        int tail;// 子类自己的变量

        public new_human() {// 构造子类对象
            super();// super关键字，引用父类的变量、方法
        }

        public new_human(String human_name, int age) {
            super(human_name, age);
        }

        public new_human(String human_name, int age, int tail) {
            this.name = human_name;
            this.age = age;
            this.tail = tail;
        }// 子类自己的构造方法
    }

    public static void main(String[] args) {
        human first = new human();
        human second = new human("小明", 18);

        System.out.println("名字:" + first.name + " 年龄:" + first.age);
        System.out.println("名字:" + second.name + " 年龄:" + second.age);
        first.sleep(8);
        second.sleep(7);

        new_human third = new new_human();
        new_human fourth = new new_human("张三", 18);
        new_human fifth = new new_human("李四", 20, 186);
        System.out.println("名字:" + third.name + " 年龄:" + third.age);
        System.out.println("名字:" + fourth.name + " 年龄:" + fourth.age);
        System.out.println("名字:" + fifth.name + " 年龄:" + fifth.age + "身高(cm):" + fifth.tail);
    }
}
输出结果：
名字:李华 年龄:18
名字:小明 年龄:18
李华睡了8小时
小明睡了7小时
名字:李华 年龄:18
名字:张三 年龄:18
名字:李四 年龄:20身高(cm):186
```

- super关键字：
  - 表示当前类的父类的引用
  - 只能出现在有继承关系的子类中
  - super两种用法：
    - super.属性名、super.方法名(参数列表)
      - 表示父类的属性和方法，和子类中的属性或方法重名时使用
    - super(参数列表)
      - 出现在子类构造方法的第一句代码时
      - 就是通过参数列表匹配父类的构造方法来创建父类对象 ##面向对象的三大基本特性：
- 封装
  - 封装是将代码及其处理的数据绑定在一起的一种编程机制，该机制保证了程序和数据都不受外部干扰且不被误用。
  - 封装的目的在于保护信息，保证数据的安全性
  - 封装包括两个方面：属性的封装和方法的封装
  - Java 提供了私有和公有的访问模式，类的公有接口代表外部的用户应该知道或可以知道的每件东西，私有的方法数据只能通过该类的成员代码来访问， 封装不是绝对的封装，如果想要访问封装起来的数据，可以通过指定的入口即可
  - 属性和方法的封装两者时相辅相成、密不可分的
- 继承 程序中的继承性是指子类拥有父类的全部特征和行为，这是类之间的一种关系。
  - 继承的特点：
    - 继承要有一定的层次结构，而且还要具备一定的可传递性
    - 子类继承了父类的所有属性和方法，但是不包括私有属性（private）和构造方法
    - 子类继承父类的属性和方法同时也可以有自己的属性和方法。
    - Java 只支持单继承。 也就是说一个子类只能有一个父类，父类可以有多个子类
    - 继承可以减少重复代码、提高了复用性和维护性
    - 继承让类与类之间产生了关系，类的耦合性增强了，父类发生变化子类也会跟着改变
- 多态 多态就是同一函数在不同类中有不同的实现；
  - 面向对象的多态性，即“一个接口，多个方法”。
  - 多态性体现在父类中定义的属性和方法被子类继承后，可以具有不同的属性或表现方式。 //在子类中修改父类方法，实现同一接口不同方法，如 father.sleep() son.sleep()同一个sleep接口，但根据不同父、子类出现不同结果
  - 多态性允许一个接口被多个同类使用，弥补了单继承的不足。
