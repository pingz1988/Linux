官方文档： https://git-scm.com/docs

## 安装部署
* 服务端
* 客户端

## 概念

## GitFlow流程

## 基本操作
* clone  
git clone https://github.com/XXX.git //注意是.git后缀

* pull **VS** fetch+merge    
  
  功能上 pull = fetch+merge ，但原理不同：pull命令相当于暴力更新，直接把远程分支的内容更新到本地仓库中的head目录（add/commit操作目录）；fetch命令只是下载远程分支代码到本地仓库中的remote目录，不更新head目录，merge命令是把remote目录合并到head目录。  
  
  pull命令会在未经确认的时候更新本地内容，fetch+merge方式更安全。

* 忽略文件（不加入版本库）

## 场景
* 当前分支A的代码没写完，被告知紧急处理另外一个分支B的bug  
在A分支执行git stash，保存未写完的代码，切换到B分支（git checkout B），解决B分支的bug后（commit+push），切回到A分支，执行git stash pop，取出当时未写完的代码

* 
