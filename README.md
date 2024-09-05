# MyNote

#### 介绍
我的学习笔记仓库，放置我的学习记录

#### 语言
主要是Java、C

#### 内容
我的笔记，比如：计算机组成原理、汇编、计算机网络、操作系统、C语言、Java、算法等

# 自动更新远程仓库

创建一个自动提交的脚本：

```sh
#!/bin/bash

# 设置工作目录为你的 Git 仓库目录
cd D:\MyNote || exit

# 获取当前日期时间
current_date=$(date "+%Y.%m.%d %H:%M:%S")

# 根据git status来检测是否有新增或修改的文件
status_output=$(git status --porcelain)

if [ -n "$status_output" ]; then
  # 使用当前日期时间作为提交信息
  commit_message="Auto commit at $current_date"

  # 将所有更改添加到暂存区
  git add . || exit

  # 提交更改，使用生成的提交信息
  git commit -m "$commit_message" || exit

  # 推送到Gitee的master分支
  git push gitee master || exit

  # 推送到GitHub的master分支
  git push github master || exit
fi
```

+ 使用 git status --porcelain 检测工作目录和暂存区的状态。该命令以机器可读的格式输出结果，便于脚本处理。
+ 检查 status_output 变量是否为空。如果不为空，表示有新增或修改的文件。
+ 如果有变化，添加所有更改、提交并推送到Gitee和GitHub的master分支。
+ 如果没有变化，脚本会输出 "没有新增或修改的文件，操作终止。" 并终止进一步操作。

在创建一个脚本，用于定时任务，每周定期执行一次更新脚本，RunAutoPush.bat：

```bat
@echo off
REM 获取脚本当前所在目录
set SCRIPT_DIR=%~dp0
REM 将反斜杠替换为正斜杠
set SCRIPT_DIR=%SCRIPT_DIR:\=/%

REM 调用 Git Bash 并执行 AutoPush.sh 脚本
"D:\Git\bin\bash.exe" -c "sh %SCRIPT_DIR%AutoPush.sh"
```

将以上批处理程序设为定时任务：

1. 按 `Win + R` 打开运行对话框，输入 `taskschd.msc`，然后按回车，打开任务计划程序。
2. 在任务计划程序窗口中，点击右侧的“创建基本任务…”。
3. 给任务命名，例如 `Run Git Bash Script`。
4. 然后设置触发器，选择“每周”，然后点击“下一步”。
5. 配置你希望脚本执行的时间和日期，例如每周一凌晨2点。
6. 然后设置“操作”，选择 该bat 文件。
7. 点击完成
