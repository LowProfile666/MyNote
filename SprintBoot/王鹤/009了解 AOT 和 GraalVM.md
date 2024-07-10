# 提供性能的技术

什么是 AOT：

Ahead-of-Time Compilation ：预编译（提前编译）它在 JEP-295 中描述，并在 Java 9 中作为实验性功能添加。

AOT 是提升 Java 程序性能的一种方法，特别是提供 JVM 的启动时间。在启动虚拟机之前，将 Java 类编译为本机代码。改进小型和大型 Java 应用程序的启动时间。

JIT (just in time）：

JIT 是现在 JVM 提高执行速度的技术，JVM 执行 Java 字节码，并将经常执行的代码编译为本机代码。这称为实时 （JIT） 编译。

当 JVM 发现某个方法或代码块运行特别频繁的时候，就会认为这是“热点代码”（Hot Spot Code)。然后 JIT会把“热点代码”编译成本地机器相关的机器码，并进行优化，然后再把编译后的机器码缓存起来，以备下次使用。

JVM 根据执行期间收集的分析信息决定 JIT 编译哪些代码。JIT 编译器速度很快，但是 Java 程序非常大，以至于 JIT 需要很长时间才能完全预热。不经常使用的 Java 方法可能根本不会被编译。

特点：在程序执行时，边运行代码边编译。JIT 编译需要时间开销，空间开销，只有对执行频繁的代码才值得编译。

AOT:静态的

JIT:动态的

# Native Image

native image: 原生镜像（本机镜像）

native image is a technology to ahead-of-time compile Java code to a standalone executable, called a native image

本机映像是一种预先将 Java 代码编译为独立可执行文件的技术，称为本机映像（原生镜像）。镜像是用于执行的文件。

通过镜像构建技术（工具）生成镜像文件（native image）。
native image 既是技术的名词也指他的生成的可执行文件。
native image 支持基于 jvm 的语言，例如 Java, Scala, Clojure, Kotlin

原生镜像文件内容包括应用程序类、来自其依赖项的类、运行时库类和来自 JDK 的静态链接本机代码（二进制文件可以直接运行，不需要额外安装 JDK）,本机映像运行在 GraalVM 上，具有更快的启动时间和更低的运行时内存开销。

在 AOT 模式下，编译器在构建项目期间执行所有编译工作，这里的主要想法是将所有的 "繁重工作"--昂贵的计算--转移到构建时间。也就是把项目都要执行的所有东西都准备好，具体执行的类，文件等。最后执行这个准备好的文件，此时应用能够快速启动。减少内存，cpu 开销（无需运行时的 JIT 的编译）。因为所有东西都是预先计算和预先编译好的。

# Native Image builder

Native Image builder（镜像构建器）：是一个实用程序，用于处理应用程序的所有类及其依赖项，包括来自JDK 的类。它静态地分析这些数据，以确定在应用程序执行期间可以访问哪些类和方法。然后，它预先将可到达的代码和数据编译为特定操作系统和体系结构的本机可执行文件

# GraalVM

GraalVM 是一个高性能 JDK 发行版，旨在加速用 Java 和其他 JVM 语言编写的应用程序，同时支持JavaScript、Ruby、Python 和许多其他流行语言。GraalVM 的多语言功能可以在单个应用程序中混合多种编程语言，同时消除外语调用成本。GraalVM 是支持多语言的虚拟机。

GraalVM 是 OpenJDK 的替代方案，包含一个名为 native image 的工具，支持预先（ahead-of-time，AOT）编译。GraalVM 执行 native image 文件启动速度更快，使用的 CPU 和内存更少，并且磁盘大小更小。这使得 Java在云中更具竞争力

目前，AOT 的重点是允许使用 GraalVM 将 Spring 应用程序部署为本机映像。Spring Boot 3 中使用 GraalVM方案提供 Native Image 支持。

GraalVM 的 "native image "工具将 Java 字节码作为输入，输出一个本地可执行文件。为了做到这一点，该工具对字节码进行静态分析。在分析过程中，该工具寻找你的应用程序实际使用的所有代码，并消除一切不必要的东西。native image 是封闭式的静态分析和编译，不支持 class 的动态加载，程序运行所需要的多有依赖项均在静态分析阶段完成



![image-20240710155339460](https://gitee.com/LowProfile666/image-bed/raw/master/img/202407101553590.png)