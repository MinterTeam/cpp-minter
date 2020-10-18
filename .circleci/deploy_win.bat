@echo off
set CONAN_LOCAL=1

for /f %%i in ('type ..\version') do set VERS=%%i

@rem default config
conan create . minter/latest -s build_type=Debug --build=missing
conan create . minter/latest -s build_type=Release --build=missing

@rem dll
conan create . minter/latest -s build_type=Debug --build=missing -o shared=True
conan create . minter/latest -s build_type=Release --build=missing -o shared=True

@rem
rem conan upload minter_tx/%VERS%@minter/latest --all -r=minter