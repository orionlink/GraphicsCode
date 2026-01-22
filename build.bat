@echo off
REM GraphicsCode 构建脚本 (Windows)

setlocal

set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Release

echo ======================================
echo 构建 GraphicsCode 项目
echo 构建类型: %BUILD_TYPE%
echo ======================================

REM 检查 Conan 是否安装
where conan >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ❌ 错误: Conan 未安装
    echo 请运行: pip install conan
    exit /b 1
)

REM 检查 Conan 配置文件
if not exist "%USERPROFILE%\.conan2" (
    echo 📦 初始化 Conan 配置...
    conan profile detect --force
)

REM 创建构建目录
if not exist build mkdir build
cd build

echo.
echo 📦 安装依赖包 (Conan)...
conan install .. --output-folder=. --build=missing -s build_type=%BUILD_TYPE%

if %ERRORLEVEL% NEQ 0 (
    echo ❌ Conan 安装失败
    exit /b 1
)

echo.
echo 🔧 配置 CMake...
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

if %ERRORLEVEL% NEQ 0 (
    echo ❌ CMake 配置失败
    exit /b 1
)

echo.
echo 🔨 编译项目...
cmake --build . --config %BUILD_TYPE%

if %ERRORLEVEL% NEQ 0 (
    echo ❌ 编译失败
    exit /b 1
)

echo.
echo ✅ 构建完成！
echo 可执行文件位置: build\%BUILD_TYPE%\sdl2_graphics.exe
echo.
echo 运行程序: %BUILD_TYPE%\sdl2_graphics.exe

endlocal
