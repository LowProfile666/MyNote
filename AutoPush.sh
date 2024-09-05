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

# 检查是否有未提交的更改
if ! git diff-index --quiet HEAD --; then
  # 添加所有更改
  git add .
  echo "git add ."
  
  # 提交更改，使用用户输入的commit信息或默认信息
  git commit -m "$commit_message"
  echo "git commit -m" + "$commit_message"
  
  # 推送到Gitee的master分支
  echo "推送代码到Gitee..."
  git push gitee master
  
  # 推送到GitHub的master分支
  echo "推送代码到GitHub..."
  git push github master
  
  echo "代码已成功提交并推送到Gitee和GitHub的master分支。"
else
  echo "没有未提交的更改。"
fi
