官方文档： https://git-scm.com/docs

## 安装部署

## 概念

## 基本操作
* pull **VS** fetch+merge    
功能上 pull = fetch+merge ，但原理不同：pull命令相当于暴力更新，直接把远程分支的内容更新到本地仓库中的head目录（add/commit操作目录）；fetch命令只是下载远程分支代码到本地仓库中的remote目录，不更新head目录，merge命令是把remote目录合并到head目录。
