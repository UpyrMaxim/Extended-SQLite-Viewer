@echo off
SetLocal EnableDelayedExpansion
(set PATH=D:\Qt_Course\5.12.2\msvc2017_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=D:\Qt_Course\5.12.2\msvc2017_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=D:\Qt_Course\5.12.2\msvc2017_64\plugins
)
%*
EndLocal
