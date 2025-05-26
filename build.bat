@echo off
REM ================================
REM  build.bat — configurable CMake build + optional test run
REM ================================

REM 1) Defaults:
set BUILD_TYPE=Release
set BUILD_TESTS=ON
set RUN_TESTS=OFF

:parse_args
if "%~1"=="" goto args_done

  if /I "%~1"=="-debug" (
    set BUILD_TYPE=Debug
  ) else if /I "%~1"=="-release" (
    set BUILD_TYPE=Release
  ) else if /I "%~1"=="-notests" (
    set BUILD_TESTS=OFF
  ) else if /I "%~1"=="-tests" (
    set BUILD_TESTS=ON
  ) else if /I "%~1"=="-runtests" (
    set RUN_TESTS=ON
  ) else (
    echo Unknown option "%~1"
    echo   Valid flags: -debug, -release, -tests, -notests, -runtests
    pause
    exit /B 1
  )

  shift
goto parse_args

:args_done
echo ============================================
echo Configuration:
echo   Build type : %BUILD_TYPE%
echo   Build tests: %BUILD_TESTS%
echo   Run tests  : %RUN_TESTS%
echo ============================================

REM 2) Prepare build directory
if not exist build (
    mkdir build
)
cd build

REM 3) CMake configure
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_TESTS=%BUILD_TESTS%
if ERRORLEVEL 1 (
  echo CMake configuration failed.
  pause
  exit /B 1
)

REM 4) Build
cmake --build . --config %BUILD_TYPE%
if ERRORLEVEL 1 (
  echo Build failed.
  pause
  exit /B 1
)

REM 5) Optionally run tests
if "%RUN_TESTS%"=="ON" (
  echo.
  echo Running tests...
  ctest --output-on-failure -C %BUILD_TYPE%
  if ERRORLEVEL 1 (
    echo Some tests failed.
    pause
    exit /B 1
  )
)

echo.
echo Build (and test, if requested) succeeded!
pause
