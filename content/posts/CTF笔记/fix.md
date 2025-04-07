

1.反编译jar包，使用IDEA反编译插件还原源代码，反编译出来还是jar包，直接解压即可

~~~ cmd
java -cp "E:\ide\IntelliJ IDEA Ultimate\plugins\java-decompiler\lib\java-decompiler.jar" org.jetbrains.java.decompiler.main.decompiler.ConsoleDecompiler -dgs=true <jar_path> <output_path>
~~~

2.导入源代码，创建一个空的Maven项目，然后将反编译后`/BOOT-INF/classes`下的源代码复制到`/src/main/java` 路径下。视check情况选择是否将`resources` 下资源文件一起导入