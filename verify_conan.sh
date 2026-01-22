#!/bin/bash

# Conan 环境验证脚本

echo "======================================"
echo "验证 Conan 环境配置"
echo "======================================"
echo ""

# 检查 Conan 安装
echo "1. 检查 Conan 安装..."
if command -v conan &> /dev/null; then
    CONAN_VERSION=$(conan --version)
    echo "   ✅ Conan 已安装: $CONAN_VERSION"
else
    echo "   ❌ Conan 未安装"
    echo "   请运行: pip install conan"
    exit 1
fi
echo ""

# 检查 CMake 安装
echo "2. 检查 CMake 安装..."
if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1)
    echo "   ✅ CMake 已安装: $CMAKE_VERSION"
else
    echo "   ❌ CMake 未安装"
    exit 1
fi
echo ""

# 检查编译器
echo "3. 检查编译器..."
if command -v g++ &> /dev/null; then
    GCC_VERSION=$(g++ --version | head -n1)
    echo "   ✅ g++ 已安装: $GCC_VERSION"
elif command -v clang++ &> /dev/null; then
    CLANG_VERSION=$(clang++ --version | head -n1)
    echo "   ✅ clang++ 已安装: $CLANG_VERSION"
else
    echo "   ❌ 未找到 C++ 编译器"
    exit 1
fi
echo ""

# 检查 Conan 配置
echo "4. 检查 Conan 配置..."
if [ -d "$HOME/.conan2" ]; then
    echo "   ✅ Conan 配置目录存在"
    echo "   默认配置文件:"
    if conan profile show >/dev/null 2>&1; then
        echo "   ✅ 默认配置已创建"
        conan profile show | head -8 | sed 's/^/   /'
    else
        echo "   ⚠️  未找到默认配置，运行 'conan profile detect' 创建"
    fi
else
    echo "   ⚠️  Conan 配置目录不存在"
    echo "   运行: conan profile detect --force"
fi
echo ""

# 测试 Conan 依赖解析
echo "5. 测试依赖解析 (不安装)..."
cd "$(dirname "$0")"
if conan graph info . 2>/dev/null | grep -q "sdl"; then
    echo "   ✅ conanfile.txt 配置正确"
else
    echo "   ⚠️  无法解析依赖，请检查 conanfile.txt"
fi
echo ""

echo "======================================"
echo "✅ 环境验证完成！"
echo "======================================"
echo ""
echo "下一步："
echo "  运行构建脚本: ./build.sh"
echo "  或查看文档: cat CONAN_README.md"
