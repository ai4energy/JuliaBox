# 编译自定义系统镜像

## **系统图像（Sysimages）**

Julia默认使用一个系统图像，当启动Julia时会自动加载。该系统图像包含了Julia编译器本身、标准库，以及一些已经编译好的代码，以减少常见操作（例如在REPL中工作）所需的时间。

有时候，如果有一些依赖项需要较长时间加载或首次调用的编译时间过长，创建一个自定义系统图像就是有益的。本文档的目的是介绍如何使用PackageCompiler创建这样的系统图像。

**自定义系统图像的缺点**

需要明确的是，使用自定义系统图像有一些缺点，因为它规避了标准的Julia包预编译系统。最大的缺点是，编译到系统图像中的包（包括它们的依赖项）将“锁定”在创建系统图像时的版本上。这意味着，无论你当前项目中安装了什么包版本，系统图像中的版本都会优先。这可能会导致问题，例如你从一个需要特定包版本的项目开始，但在系统图像中编译了另一个版本。

因此，只有在这些包的加载时间成为重要问题并且这些包不经常更新时，才建议将包放入系统图像中。此外，将“工作流程包”（如Revise.jl和OhMyREPL.jl）编译到系统图像中可能会有意义。

另外一些情景是，或许你想在一定程度上保护你的代码。

## **使用PackageCompiler创建系统图像**

PackageCompiler提供了`create_sysimage`函数用于创建系统图像。它的第一个参数是要嵌入到生成的系统图像中的一个或多个包的列表。默认情况下，给定的包将从活动项目中加载，但可以通过使用`project`关键字来指定特定项目的路径。生成的系统图像的位置由`sysimage_path`关键字指定。创建了系统图像之后，使用命令标志`-Jpath/to/sysimage`（或`--sysimage=path/to/sysimage`）将使用给定的系统图像启动Julia。

以下是一个示例，演示如何在一个单独的项目中创建一个新的系统图像，并在其中包含`Example.jl`包。使用`Base.loaded_modules`可以看到，无需显式导入，该包已被加载。

```shell

# 创建一个新的环境并激活它
mkdir NewSysImageEnv 
cd NewSysImageEnv 
julia -q
```
```julia
using PackageCompiler
using Pkg

# 切换到Pkg模式激活当前目录的新环境
Pkg.activate(".")

# 添加要包含在系统图像中的包
import Pkg
Pkg.add("Example")

# 创建系统图像
create_sysimage(["Example"], sysimage_path="ExampleSysimage.dll")

# 退出Julia REPL
exit()
```

在此示例中，`ExampleSysimage.dll` 文件是你创建的系统图像文件。

需要注意的是，系统图像默认以“增量”的方式创建，这意味着它们会添加到运行PackageCompiler的进程的系统图像中。可以通过传递`incremental=false`关键字来创建非增量的系统图像，从头开始创建一个新的系统图像。然而，这将丢失Julia捆绑的系统图像提供的特殊预编译，这是在Julia重新启动后使REPL和包管理器无需重新编译的原因。因此，除非在系统图像创建的特殊情况下（对于应用程序而言情况不同），`incremental=false` 不太有用。

作为替代方案，考虑使用其他机制来传递`-J`标志给Julia，如创建桌面快捷方式或shell别名，例如 `$ alias julia='julia -J/path/to/sysimage.so'`。

## **使用创建的系统图像**

我们可以在shell下输入如下命令查看julia的命令行参数：
```shell
julia --help
```
可以看到有个选项`-J, --sysimage`可以用来指定使用的系统镜像，因此我们可以以如下命令启动我们自己的julia镜像:
```shell
julia --sysimage ./ExampleSysimage.dll
```