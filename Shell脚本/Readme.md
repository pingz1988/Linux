```shell
# 获取当前svn版本号
SVN_VERSION=`svn up|grep revision|awk '{print $3}'|awk -F'.' '{print $1}'`
echo "current svn version: ${SVN_VERSION}"
```
