# Conan 常用命令速查表

## 🔍 查看系统 SDL2 版本

### macOS (Homebrew)
```bash
# 查看 Homebrew 安装的版本
brew list sdl2 --versions

# 查看详细信息
brew info sdl2

# 查看安装位置
brew --prefix sdl2
```

### 使用 pkg-config
```bash
# 查看版本
pkg-config --modversion sdl2

# 查看编译选项
pkg-config --cflags sdl2
pkg-config --libs sdl2
```

### Linux
```bash
# Debian/Ubuntu
dpkg -l | grep sdl2

# RPM 系统
rpm -qa | grep sdl2
```

---

## 📦 Conan 包管理命令

### 查看已安装的包

```bash
# 列出所有包
conan list "*"

# 列出特定包（如 SDL）
conan list "sdl/*"

# 显示包的详细信息
conan list "sdl/2.30.9"
```

### 搜索可用的包版本

```bash
# 搜索 SDL 的所有版本
conan search sdl --remote=conancenter

# 在线搜索（需要网络）
conan search sdl -r conancenter
```

### 清理缓存

```bash
# 删除特定包
conan remove "sdl/*" -c

# 删除特定版本
conan remove "sdl/2.30.9" -c

# 删除所有缓存（谨慎使用！）
conan remove "*" -c

# 只删除源码缓存，保留二进制
conan remove "sdl/*" --src
```

### 查看缓存信息

```bash
# 查看 Conan 缓存目录
echo $HOME/.conan2

# 查看缓存大小
du -sh $HOME/.conan2

# 查看特定包的缓存
du -sh $HOME/.conan2/p/sdl*
```

---

## 🔄 版本更新最佳实践

### 场景 1：更新依赖版本

```bash
# 1. 修改 conanfile.txt 中的版本号
# 例如：sdl/2.30.9 → sdl/2.32.0

# 2. 清理旧版本（可选但推荐）
conan remove "sdl/2.30.9" -c

# 3. 重新安装
./build.sh
```

### 场景 2：清理损坏的缓存

```bash
# 如果看到 "corrupted source folder" 警告
conan remove "sdl/*" -c
./build.sh
```

### 场景 3：完全重置 Conan 环境

```bash
# 1. 备份配置（可选）
cp -r ~/.conan2/profiles ~/.conan2/profiles.backup

# 2. 删除所有缓存
conan remove "*" -c

# 3. 或者完全删除 Conan 目录
rm -rf ~/.conan2

# 4. 重新初始化
conan profile detect --force

# 5. 重新构建项目
./build.sh
```

---

## 🎯 常见问题解决

### 问题：构建卡住或下载很慢

```bash
# 清理并重试
conan remove "sdl/*" -c
./build.sh
```

### 问题：想使用系统已安装的 SDL2

```bash
# 方案 1: 创建不使用 Conan 的构建
mkdir build_local && cd build_local
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# 方案 2: 修改 CMakeLists.txt 不依赖 Conan
# （需要手动修改配置）
```

### 问题：版本冲突

```bash
# 查看当前安装的版本
conan list "sdl/*"

# 删除所有版本
conan remove "sdl/*" -c

# 重新安装指定版本
./build.sh
```

---

## 📊 Conan 配置

### 查看配置

```bash
# 显示默认配置
conan profile show

# 查看配置文件路径
conan profile path default

# 列出所有配置文件
conan profile list
```

### 修改配置

```bash
# 编辑配置文件
conan profile path default  # 显示路径
# 然后用编辑器打开该文件

# 或直接修改
vim ~/.conan2/profiles/default
```

---

## 🚀 快速命令参考

| 命令 | 说明 |
|------|------|
| `conan list "*"` | 列出所有包 |
| `conan remove "pkg/*" -c` | 删除包缓存 |
| `conan profile show` | 显示配置 |
| `conan search pkg` | 搜索包 |
| `./build.sh` | 构建项目 |
| `brew list sdl2 --versions` | 查看系统 SDL2 版本（macOS） |

---

## 💡 提示

1. **第一次构建慢是正常的**：Conan 需要下载和编译包
2. **后续构建会很快**：包会被缓存
3. **定期清理缓存**：可以释放磁盘空间
4. **使用版本锁定**：确保团队使用相同版本
5. **遇到问题先清理缓存**：大部分问题可以通过清理缓存解决

---

## 📚 相关文档

- [README.md](README.md) - 项目主文档和快速开始指南
- [Conan 官方文档](https://docs.conan.io/)
- [SDL2 官方文档](https://wiki.libsdl.org/)
- [CMake 官方文档](https://cmake.org/documentation/)