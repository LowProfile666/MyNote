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
