@echo off

rmdir /S /Q    prj\vs10\ipch
rmdir /S /Q    prj\vs10\Debug
rmdir /S /Q    prj\vs10\Release
del   /F /Q /A prj\vs10\*.suo
del   /F /Q    prj\vs10\*.sdf
del   /F /Q    prj\vs10\*.opensdf
del   /F /Q    prj\vs10\*.vcxproj.user
del   /F /Q    prj\vs10\*.vcxproj.filters
