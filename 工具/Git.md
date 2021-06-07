Git官方文档： https://git-scm.com/docs

## 流程
* Git flow  
清晰可控，但相对复杂，需长期维护master、dev这2个分支，适用于版本发布，即一段时间产生一个版本
* Github flow  
适用于持续发布（如网络项目）  
它是针对以下问题（痛点）： 
* **Gitlab flow**  
是上述2个流程的结合，采取“上游优先”原则，尽可能在上游修改，下游去取最新代码来合并。  
11个规则：https://www.cnblogs.com/linuxprobe/p/5778525.html  
它是针对以下问题（痛点）：

## 文档

位于安装目录下，D:\Program Files\Git\mingw64\share\doc\git-doc

可直接用 git help XXX 来查看相关命令的用法。

## 配置

```shell
git config --global user.email "807961446@qq.com"
git config --global user.name "pingz"
```

## 基本操作

* 查看log

  ```shell
  git log <--pretty=oneline/fuller>  # 可用pretty指定的参数来显示log
  ```

  

* 查看当前状态

  ```shell
  git status
  ```

  

* clone

  ```shell
  git clone https://github.com/XXX.git  # .git后缀可带可不带
  ```

* fetch

   fetch命令就是一次下载操作，它会将远程新增加的节点以及引用(分支/HEAD)的状态下载到本地。

  ```shell
  git fetch "远程仓库地址/分支名"
  ```

   clone 或 fetch 都会将远程仓库的所有提交、引用保存到本地。

* pull

  从远程仓库的某个引用拉取代码（强行拉取），pull 在效果上与 fetch+merge 类似，实则不同，使用时注意区分

  ```shell
  git pull "远程分支名（xxx.git URI）"
  ```
  
* add

  加入到暂存区

  ```shell
  git add 文件路径  # 添加某个文件到暂存区
  git add .  # 添加所有文件到暂存区
  ```

* 清空暂存区

  ```shell
  git reset HEAD "文件名"
  ```

* commit

  提交暂存区中的文件到本地，提交后会生成一个新的提交节点

  ```shell
  git commit -m "注释、描述信息"  # git 不上传空目录，如果需要上传空目录，在空目录下创建.gitkeep，并配置不忽略此文件
  git commit -am "注释、描述信息"  # 提交所有修改、要删除的文件，但不添加文件；保险起见，执行 add. 命令
  ```

* push

  将本地修改推送到远程仓库

  ```shell
  git push "远程分支名"
  ```

  add - commit - push 这是一套提交操作。

* 分支命令

  ```shell
  git branch "分支名"  # 创建一个分支后该分支会与HEAD指向同一节点
  git checkout -b "分支名"  # 创建分支并切换到该分支
  git checkout "分支名"  # 切换分支
  git branch -d "分支名"  # 删除指定分支，注意，删除分支时，当前分支不能停留在要删除的分支上，要切换到其他任意分支，再去删除目标分支
  git merge "分支名/节点哈希值"  # 最常用的合并命令，合并后产生新的节点，每个节点都是严格按照时间排列
  git rebase "分支名/节点哈希值"  # 合并，合并后不产生新的节点，这使得提交历史看起来更加线性、干净，但提交的节点不是真正的按时间排序，被合并的节点时间不管是在目标分支最后节点的前面或者后面，都会将被合并节点放到目标分支的最后
  git cherry-pick "节点哈希值"  # 选择节点进行合并
  ```

* 回退
  
  ```shell
  git log --pretty=oneline  # --pretty 美观显示提交log 
  git reset HEAD~N  # 回退N个提交，git文档中没查到该用法
  git reset --hard N  # 回退到指定的提交N
  git reset --hard HEAD^  # 回退到上一次提交
  ```
  
* 打 tag
  
  ```shell
  git tag  # 列出已有tag
  git tag TAG_NAME  # 创建tag
  git tag -a TAG_NAME -m "描述信息"  # 创建tag，并加注释描述信息
  git tag -a TAG_NAME N -m "描述信息"  # 给指定的某个commit号N打tag
  git push origin TAG_NAME  # 推送tag到远程分支
  ```
  
  
  
* 合并主分支到本地分支
  
  ```shell
  git checkout "本地分支名"
  git pull "远程分支名（xxx.git URI）"  # 执行 pull 前，需要将当前修改 commit或 stash，否则可能会有合并冲突，而导致部分文件 pull 不成功
  ```
  
  
  
* pull **VS** fetch+merge    
  
  功能上 pull = fetch+merge ，但原理不同：pull命令相当于暴力更新，直接把远程分支的内容更新到本地仓库中的head目录（add/commit操作目录）；fetch命令只是下载远程分支代码到本地仓库中的remote目录，不更新head目录，merge命令是把remote目录合并到head目录。  
  
  pull命令会在未经确认的时候更新本地内容，fetch+merge方式更安全。

* 权限控制  

* 忽略文件（不加入版本库）

## 问题  
* push 报错

  fatal: unable to access 'https://github.com/pingz1988/Linux/': OpenSSL SSL_read: Connection was reset, errno 10054

  ```shell
  git config --global http.sslVerify "false"
  ```

  执行上述命令后，再 push。

* 删除分支后，其它与该分支有关系的分支历史记录会不会被删除？  

* 多产品来自同一个master，此时如何作分支管理？

* 如何在Gitlab中进行issue跟踪？

* 产品发布一段时间后，线上出现了bug，从交付分支拉出hotfix分支，修复后merge到交付分支和master分支（或开发分支），如果在产品发布后的这段时间里，master分支（或开发分支）进行了重大重构，hotfix如何merger回master分支（或开发分支）？

## 应用场景
* 当前**分支A**的代码没写完，被告知紧急处理另外一个**分支B**的bug  
在A分支执行git stash，保存未写完的代码，切换到B分支（git checkout B），解决B分支的bug后（commit+push），切回到A分支，执行git stash pop，取出当时未写完的代码