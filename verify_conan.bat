@echo off
REM Conan 环境验证脚本 (Windows)

setlocal enabledelayedexpansion

echo ======================================
echo 验证 Conan 环境配置
echo ======================================
echo.

REM 检查 Conan 安装
echo 1. 检查 Conan 安装...
where conan >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    for /f "tokens=*" %%i in ('conan --version') do set CONAN_VERSION=%%i
    echo    ✅ Conan 已安装: !CONAN_VERSION!
) else (
    echo    ❌ Conan 未安装
    echo    请运行: pip install conan
    exit /b 1
)
echo.

REM 检查 CMake 安装
echo 2. 检查 CMake 安装...
where cmake >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    for /f "tokens=*" %%i in ('cmake --version ^| findstr /C:"cmake version"') do set CMAKE_VERSION=%%i
    echo    ✅ CMake 已安装: !CMAKE_VERSION!
) else (
    echo    ❌ CMake 未安装
    exit /b 1
)
echo.

REM 检查编译器
echo 3. 检查编译器...
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo    ✅ MSVC 编译器可用
) else (
    echo    ⚠️  MSVC 编译器未找到
    echo    请在 "Developer Command Prompt for VS" 中运行此脚本
)
echo.

REM 检查 Conan 配置
echo 4. 检查 Conan 配置...
if exist "%USERPROFILE%\.conan2" (
    echo    ✅ Conan 配置目录存在
    echo    默认配置文件:
    conan profile show >nul 2>nul
    if !ERRORLEVEL! EQU 0 (
        echo    ✅ 默认配置已创建
    ) else (
        echo    ⚠️  未找到默认配置，运行 'conan profile detect' 创建
    )
) else (
    echo    ⚠️  Conan 配置目录不存在
    echo    运行: conan profile detect --force
)
echo.

echo ======================================
echo ✅ 环境验证完成！
echo ======================================
echo.
echo 下一步：
echo   运行构建脚本: build.bat
echo   或查看文档: type CONAN_README.md

endlocal