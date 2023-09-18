# 编译julia代码成可执行文件

***julia本身是个动态语言，用它来创建可执行文件不是一个常见的需求。本文只是展示这么做可行。***

## 创建julia包myapp

创建一个 Julia 包（package）需要一些基本步骤。以下是一个创建 Julia 包的一般步骤：

1. **创建包目录**：创建一个用于存放你的 Julia 包的目录。你可以在命令行中使用以下命令来创建一个新目录并进入该目录：

   ```bash
   mkdir myappdir
   cd myappdir
   ```

2. **初始化包**：在包目录中，使用 Julia 的 `Pkg` 模块来初始化一个新的包。运行以下命令：

   ```julia
   using Pkg
   Pkg.generate("myapp")
   ```

   这将在当前目录中创建一个名为 "myapp" 的新包。

3. **编辑包代码**：进入包的源代码目录，通常是 `src/`，然后开始编辑你的包代码。你可以使用任何文本编辑器或集成开发环境（IDE）来编辑 Julia 代码。通常你可以使用vscode。

## 创建julia_main函数

在使用 Julia 创建可执行文件（EXE）时，通常需要至少一个包，因为 Julia 主要是通过包的方式组织和管理代码的。即使你的应用程序非常简单，仍然需要至少一个包来包含 `julia_main` 函数以及其他必要的 Julia 代码。

这是因为 `PackageCompiler` 以及其他 Julia 编译工具通常是基于 Julia 包来工作的，它们期望有一个包来编译为可执行文件。即使你的包非常小，只包含一个文件，也建议将其组织为一个最小的 Julia 包。

下面是一个示例：

```julia
# 定义你的 julia_main 函数
function julia_main()::Cint
    println("Hello from Julia EXE!")
    return 0  # 调用应用程序逻辑中的函数
end
```

在这个示例中，`myapp.jl` 文件定义了 `myapp`模块，它只有一个函数`julia_main`，因为要有返回值给系统，说明了返回值的类型是Cint。

如果你的代码较为复杂，你可以将应用程序的所有代码放在一个单独的 Julia 文件中，然后使用 `include` 函数在 `julia_main` 函数中加载该文件。这种方式可以让你的应用程序只有一个文件而没有额外的包，但仍然需要一个包来包含 `julia_main` 函数。

下面是一个示例：

```julia
# 在 julia_main.jl 中定义你的 julia_main 函数
function julia_main()
    println("Hello from Julia EXE!")

    # 在这里添加你的应用程序的主要功能
    # 例如，你可以调用其他函数或模块

    include("myapp_logic.jl")  # 加载应用程序逻辑
    myapp_logic()  # 调用应用程序逻辑中的函数
end

# 在 myapp_logic.jl 文件中定义应用程序逻辑
function myapp_logic()
    # 这里包含了应用程序的实际功能
    result = 1 + 2
    println("Result: $result")
end
```

在这个示例中，`julia_main.jl` 文件包含了 `julia_main` 函数，它加载了一个名为 `myapp_logic.jl` 的文件，该文件包含了应用程序的主要功能。虽然只有两个文件，但仍然需要一个包（包含 `julia_main` 函数的文件）来创建 Julia 可执行文件。

总之，Julia 可执行文件需要一个包来运行，但你可以将所有代码组织在一个文件中，以减少包的复杂性。
## 编译成exe文件

我们可以使用 PackageCompiler 将 Julia 代码编译成可执行文件（EXE 文件）。

1. **安装 PackageCompiler 包**：首先，确保你已经安装了 PackageCompiler 包。你可以在 Julia REPL 中使用以下命令安装它：

   ```julia
   using Pkg
   Pkg.add("PackageCompiler")
   ```

2. **导入 PackageCompiler 包**：在你的 Julia 会话中，导入 PackageCompiler 包：

   ```julia
   using PackageCompiler
   ```

3. **执行编译EXE**：运行编译器来生成可执行文件。

   ```julia
   create_app("myapp", "build")
   ```

4. **测试可执行文件**：在生成可执行文件后，你可以通过运行它来测试它是否正常工作。如果一切顺利，你应该能够在不安装 Julia 的情况下运行你的应用程序。在此时我们应该在当前目录下生成了myappcompiled目录。进入这个myappcompiled目录会有个bin目录，里头就有myapp.exe。执行它就好。

5. **简化一下**

   ```julia
   julia --project=. compile.jl
   ```  

如有疑问请参考PackageCompiler官方文档，以及 https://github.com/lucifer1004/MonkeyLang.jl 中compile目录下的文件。