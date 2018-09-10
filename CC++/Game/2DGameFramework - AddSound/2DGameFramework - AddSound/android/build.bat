@echo off
set ANDROID_NDK=G:\android-ndk32-r10b-windows-x86\android-ndk-r10b
echo ======================
echo === Begin build SO ===
echo ======================
call %ANDROID_NDK%\ndk-build

echo ======================
echo === End SO ===
echo ======================
pause