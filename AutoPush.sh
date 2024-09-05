#!/bin/bash

# 获取当前日期时间
current_date=$(date "+%Y.%m.%d %H:%M:%S")

# 提示用户输入commit备注信息
read -p "请输入commit备注信息（或直接按回车使用默认信息）： " user_commit_message

# 如果用户没有输入备注信息，使用默认信息
commit_message=${user_commit_message:-$current_date}

# 拉取最新的代码以确保本地仓库是最新的
# echo "拉取Gitee的最新代码..."
# git pull gitee master

# echo "拉取GitHub的最新代码..."
# git pull github master

# 根据git status来检测是否有新增或修改的文件
status_output=$(git status --porcelain)

if [ -n "$status_output" ]; then
  # 如果有变化，将所有更改添加到暂存区
  echo "执行：git add .\n"
  git add .
  
  echo "\n"

  # 提交更改，使用用户输入的commit信息或默认信息
  echo "执行：git commit -m " +  "$commit_message" + "\n"
  git commit -m "$commit_message"
  
  echo "\n"

  # 推送到Gitee的master分支
  echo "推送代码到Gitee..."
  git push gitee master

  echo "\n"
  
  # 推送到GitHub的master分支
  echo "推送代码到GitHub..."
  git push github master

  echo "\n"
  
  echo "代码已成功提交并推送到Gitee和GitHub的master分支。"
else
  echo "没有新增或修改的文件，操作终止。"
fi
