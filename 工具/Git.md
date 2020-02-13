Git官方文档： https://git-scm.com/docs

## 安装部署
* 服务端  
GitLab: https://docs.gitlab.com/ee/README.html
* 客户端  
TortoiseGit

## 概念

## 流程
* Git flow  
清晰可控，但相对复杂，需长期维护master、dev这2个分支，适用于版本发布，即一段时间产生一个版本
* Github flow  
适用于持续发布（如网络项目）
* Gitlab flow  
是上述2个流程的结合，采取“上游优先”原则，尽可能在上游修改，下游去取最新代码来合并

## 基本操作
* clone  
git clone https://github.com/XXX.git   //注意是.git后缀

* pull **VS** fetch+merge    
  
  功能上 pull = fetch+merge ，但原理不同：pull命令相当于暴力更新，直接把远程分支的内容更新到本地仓库中的head目录（add/commit操作目录）；fetch命令只是下载远程分支代码到本地仓库中的remote目录，不更新head目录，merge命令是把remote目录合并到head目录。  
  
  pull命令会在未经确认的时候更新本地内容，fetch+merge方式更安全。

* 权限控制  

* 忽略文件（不加入版本库）

## 场景
* 当前**分支A**的代码没写完，被告知紧急处理另外一个**分支B**的bug  
在A分支执行git stash，保存未写完的代码，切换到B分支（git checkout B），解决B分支的bug后（commit+push），切回到A分支，执行git stash pop，取出当时未写完的代码

* 
