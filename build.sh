#!/bin/bash

# GraphicsCode 构建脚本 (Linux/macOS)

set -e

BUILD_TYPE=${1:-Release}

echo "======================================"
echo "构建 GraphicsCode 项目"
echo "构建类型: $BUILD_TYPE"
echo "======================================"

# 检查 Conan 是否安装
if ! command -v conan &> /dev/null
then
    echo "❌ 错误: Conan 未安装"
    echo "请运行: pip install conan"
    exit 1
fi

# 检查 Conan 配置文件
if [ ! -d "$HOME/.conan2" ]; then
    echo "📦 初始化 Conan 配置..."
    conan profile detect --force
fi

# 清理旧的构建目录（可选）
# rm -rf build

# 创建构建目录
mkdir -p build
cd build

echo ""
echo "📦 安装依赖包 (Conan)..."
conan install .. --output-folder=. --build=missing -s build_type=$BUILD_TYPE

echo ""
echo "🔧 配置 CMake..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE

echo ""
echo "🔨 编译项目..."
cmake --build . --config $BUILD_TYPE

echo ""
echo "✅ 构建完成！"
echo "可执行文件位置: build/sdl2_graphics"
echo ""
echo "运行程序: ./sdl2_graphics"
