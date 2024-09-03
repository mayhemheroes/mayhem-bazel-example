@echo off
setlocal

REM Define the LLVM version and download URL
set LLVM_VERSION=17.0.3
set LLVM_URL=https://github.com/llvm/llvm-project/releases/download/llvmorg-%LLVM_VERSION%/LLVM-%LLVM_VERSION%-win64.exe
set LLVM_INSTALLER=LLVM-%LLVM_VERSION%-win64.exe
set LLVM_DIR=%ProgramFiles%\LLVM

REM Download the LLVM installer
echo Downloading LLVM %LLVM_VERSION%...
curl -L -o %LLVM_INSTALLER% %LLVM_URL%

REM Check if the download was successful
if not exist %LLVM_INSTALLER% (
    echo Error: Failed to download LLVM from %LLVM_URL%.
    exit /b 1
)

REM Install LLVM to the default Program Files directory
echo Installing LLVM to %LLVM_DIR%...
start /wait "" %LLVM_INSTALLER% /S /D=%LLVM_DIR%

REM Check if the installation was successful
if not exist "%LLVM_DIR%\bin\clang.exe" (
    echo Error: LLVM installation failed.
    exit /b 1
)

REM Set the BAZEL_LLVM environment variable
setx BAZEL_LLVM "%LLVM_DIR%" /M

REM Verify the BAZEL_LLVM environment variable
echo BAZEL_LLVM is set to %LLVM_DIR%

REM Cleanup the installer
echo Cleaning up...
del %LLVM_INSTALLER%

echo LLVM %LLVM_VERSION% has been installed successfully.

endlocal
