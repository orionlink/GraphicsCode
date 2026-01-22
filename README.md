# GraphicsCode

一个使用 C++ 和 SDL2 构建的图形渲染项目，支持点、线、三角形等基本图元的绘制。

本项目使用 Conan 2.x 作为包管理工具，支持跨平台构建（Windows、Linux、macOS）。

## 📋 目录

- [快速开始](#-快速开始)
- [环境要求](#-环境要求)
- [构建步骤](#-构建步骤)
- [项目结构](#-项目结构)
- [依赖管理](#-依赖管理)
- [常见问题](#-常见问题)
- [IDE 集成](#-ide-集成)
- [相关文档](#-相关文档)

---

## 🚀 快速开始

### Linux / macOS

```bash
# 1. 验证环境（可选）
./verify_conan.sh

# 2. 构建项目
./build.sh

# 3. 运行程序
cd build
./sdl2_graphics
```

### Windows

```cmd
# 1. 验证环境（可选）
verify_conan.bat

# 2. 构建项目
build.bat

# 3. 运行程序
cd build\Release
sdl2_graphics.exe
```

---

## 📋 环境要求

### 必需组件

#### 1. Conan 包管理器

**macOS**:
```bash
# 推荐使用 Homebrew
brew install conan

# 或使用 pipx
brew install pipx
pipx install conan
```

**Windows / Linux**:
```bash
pip install conan
```

安装后验证：
```bash
conan --version  # 应显示 2.x 版本
```

#### 2. 初始化 Conan 配置

首次使用时需要检测系统配置：

```bash
conan profile detect --force
```

这会在 `~/.conan2/profiles/default` 创建默认配置文件。

#### 3. CMake

- **macOS**: `brew install cmake`
- **Windows**: 从 [cmake.org](https://cmake.org/download/) 下载安装
- **Linux**: `sudo apt install cmake` 或 `sudo yum install cmake`

#### 4. C++ 编译器

- **macOS**: Xcode Command Line Tools
  ```bash
  xcode-select --install
  ```
- **Windows**: Visual Studio 2019/2022（包含 MSVC）
- **Linux**: GCC
  ```bash
  sudo apt install build-essential  # Debian/Ubuntu
  ```

---

## 🔨 构建步骤

### 自动构建（推荐）

项目提供了跨平台构建脚本，自动处理所有步骤：

```bash
# Linux/macOS
./build.sh          # Release 模式
./build.sh Debug    # Debug 模式

# Windows
build.bat           # Release 模式
build.bat Debug     # Debug 模式
```

### 手动构建

如果需要更多控制，可以手动执行各步骤：

#### 1. 安装依赖

```bash
mkdir build && cd build
conan install .. --output-folder=. --build=missing -s build_type=Release
```

参数说明：
- `--output-folder=.`: 输出到当前目录
- `--build=missing`: 如果预编译包不可用，则从源码构建
- `-s build_type=Release`: 指定构建类型（Release/Debug）

#### 2. 配置 CMake

**Linux/macOS**:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```

**Windows**:
```cmd
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

#### 3. 编译项目

```bash
cmake --build . --config Release
```

---

## 📁 项目结构

```
GraphicsCode/
├── src/                          # 源代码目录
│   ├── main.cpp                  # 主程序入口
│   ├── color.h                   # 颜色定义
│   ├── graphics_renderer.h/cpp   # 图形渲染器
│   ├── pixels_buffer.h/cpp       # 像素缓冲区
│   ├── sdl2_window.h/cpp         # SDL2 窗口封装
│   ├── math/                     # 数学库
│   │   ├── vector.h              # 向量运算
│   │   ├── point.h               # 点定义
│   │   ├── line.h                # 线定义
│   │   └── bounding_box.h        # 包围盒
│   └── primitive/                # 图元绘制
│       ├── primitive.h           # 图元基类
│       ├── point_primitive.h/cpp # 点绘制
│       ├── line_primitive.h/cpp  # 线绘制
│       ├── antialiased_line_primitive.h/cpp  # 抗锯齿线
│       └── triangle_primitive.h/cpp          # 三角形绘制
├── build/                        # 构建输出目录
├── CMakeLists.txt               # CMake 配置
├── conanfile.txt                # Conan 依赖配置
├── build.sh                     # Linux/macOS 构建脚本
├── build.bat                    # Windows 构建脚本
├── verify_conan.sh              # Linux/macOS 环境验证脚本
├── verify_conan.bat             # Windows 环境验证脚本
├── README.md                    # 本文件
└── CONAN_COMMANDS.md           # Conan 命令速查表
```

---

## 📦 依赖管理

项目依赖配置在 `conanfile.txt` 中：

```ini
[requires]
sdl/2.30.9          # SDL2 图形库

[generators]
CMakeDeps           # 生成 CMake 依赖查找文件
CMakeToolchain      # 生成 CMake 工具链文件

[options]
sdl/*:shared=False  # 使用静态链接（便于分发）

[layout]
cmake_layout        # 使用标准 CMake 布局
```

### 常用 Conan 命令

```bash
# 查看已安装的包
conan list "*"
conan list "sdl/*"

# 清理缓存
conan remove "sdl/*" -c        # 删除 SDL 缓存
conan remove "*" -c            # 删除所有缓存

# 查看配置
conan profile show

# 查看系统 SDL2 版本
brew list sdl2 --versions      # macOS
```

📚 **完整命令参考**: 查看 [CONAN_COMMANDS.md](CONAN_COMMANDS.md) 获取详细的 Conan 命令使用说明。

---

## 🛠️ 常见问题

### 1. Conan 找不到预编译包

如果出现 "No binary packages found"，Conan 会自动从源码构建，这是正常的。第一次构建会比较慢，但后续会使用缓存。

### 2. 构建卡住或下载很慢

```bash
# 清理损坏的缓存并重试
conan remove "sdl/*" -c
./build.sh
```

### 3. macOS 上 pip 安装 Conan 失败

macOS 系统限制了全局 pip 安装，使用以下方式：

```bash
# 方式 1: 使用 Homebrew（推荐）
brew install conan

# 方式 2: 使用 pipx
brew install pipx
pipx install conan
```

### 4. Windows 上 CMake 找不到编译器

确保已安装 Visual Studio，并在 "开始菜单" 中使用 **"Developer Command Prompt for VS"** 运行构建命令。

### 5. macOS 上缺少 Xcode 命令行工具

```bash
xcode-select --install
```

### 6. 想使用系统已安装的 SDL2

如果本地已有 SDL2（如通过 Homebrew 安装），可以临时不使用 Conan：

```bash
mkdir build_local && cd build_local
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

注意：这种方式不保证跨平台一致性。

### 7. 清理并重新构建

```bash
# 删除构建目录
rm -rf build

# 清理 Conan 缓存（可选）
conan remove "sdl/*" -c

# 重新构建
./build.sh  # 或 build.bat
```

### 8. 修改 Conan 配置

```bash
# 查看当前配置
conan profile show

# 查看配置文件路径
conan profile path default

# 编辑配置（需要手动打开编辑器）
vim ~/.conan2/profiles/default
```

---

## 🎯 IDE 集成

### CLion

1. 打开项目
2. CLion 会自动检测 Conan 配置
3. 选择构建配置（Debug/Release）即可

### Visual Studio Code

1. 安装 **CMake Tools** 扩展
2. 选择 Kit（编译器）
3. 在 `.vscode/settings.json` 中配置：
   ```json
   {
     "cmake.configureArgs": [
       "-DCMAKE_TOOLCHAIN_FILE=${workspaceFolder}/build/conan_toolchain.cmake"
     ]
   }
   ```

### Visual Studio

1. 打开 CMake 项目（文件 → 打开 → CMake...）
2. 确保已安装 "用于 Windows 的 C++ CMake 工具"
3. 右键点击 `CMakeLists.txt` → "配置缓存"

---

## ✨ 项目特性

### 当前实现的功能

- ✅ SDL2 窗口管理和事件循环
- ✅ 像素级绘制缓冲区
- ✅ 基础图元绘制
  - 点绘制
  - Bresenham 直线算法
  - Wu氏抗锯齿直线
  - 三角形绘制
- ✅ 颜色插值和渐变
- ✅ 数学库（向量、点、线、包围盒）

### 构建特性

- ✅ **跨平台支持**: Windows、Linux、macOS 一致的构建流程
- ✅ **自动依赖管理**: Conan 自动下载和配置 SDL2
- ✅ **一键构建**: 简单的构建脚本
- ✅ **静态链接**: 可执行文件独立运行，无需额外 DLL
- ✅ **版本锁定**: 确保团队使用相同的依赖版本
- ✅ **Debug/Release**: 支持多种构建配置

---

## 📚 相关文档

- [CONAN_COMMANDS.md](CONAN_COMMANDS.md) - Conan 命令速查表和最佳实践
- [Conan 官方文档](https://docs.conan.io/)
- [SDL2 官方文档](https://wiki.libsdl.org/)
- [CMake 官方文档](https://cmake.org/documentation/)

---

## 🔄 版本历史

### v2.0 - Conan 集成
- 添加 Conan 包管理支持
- 跨平台构建脚本
- 环境验证工具
- 完善的文档

### v1.0 - 初始版本
- 基础图形渲染功能
- SDL2 窗口管理
- 图元绘制实现

---

## 📝 许可证

[]

---

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

---

## 📞 联系方式

[pisnebula@gmail.com]
