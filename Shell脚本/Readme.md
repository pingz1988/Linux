```shell
# 获取当前svn版本号，注意最外层的符号是`，不是单引号'
SVN_VERSION=`svn up|grep revision|awk '{print $3}'|awk -F'.' '{print $1}'`
echo "current svn version: ${SVN_VERSION}"
```
