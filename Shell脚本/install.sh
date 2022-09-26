```shell

#!/bin/sh

show_usage()
{
	echo "---------------------------------------"
	echo "Usage:"
	echo "       ./installs.sh namd"
	echo "       ./installs.sh namdHttpd"
	echo "       ./installs.sh both"
	echo "---------------------------------------"
}

install_namd()
{
	TAR=namd.tar.gz
	DIR=/mvtech/namd  #默认安装到 /mvtech/namd
	NAME=namd
	SEVC=$NAME.service
	if [ ! -f $TAR ]; then
		echo "install ${NAME} failed: ${TAR} not exist."
		return
	fi
	#显示md5
	md5sum $TAR
	#解压
	mkdir -p $DIR && tar zxvf $TAR -C $DIR && cd $DIR
	#开机启动
	cp $SEVC /usr/lib/systemd/system/$SEVC
	systemctl daemon-reload
	systemctl start $NAME
}

install_namdHttpd()
{
	TAR=namdHttpd.tar.gz
	DIR=/mvtech/namdHttpd  #默认安装到 /mvtech/namdHttpd
	NAME=namdHttpd
	SEVC=$NAME.service
	if [ ! -f $TAR ]; then
		echo "install ${NAME} failed: ${TAR} not exist."
		return
	fi
	#显示md5
	md5sum $TAR
	#解压
	mkdir -p $DIR && tar zxvf $TAR -C $DIR/ && cd $DIR
	#生成自签名证书
	openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -keyout namdHttpd.key -out namdHttpd.pem
	#开机启动
	cp $SEVC /usr/lib/systemd/system/$SEVC
	systemctl daemon-reload
	systemctl start $NAME
}

install_both()
{
	install_namd
	install_namdHttpd
}

if [ $# -ne 1 ]; then
	echo "Invalid args!"
	show_usage
	exit 1
fi

case $1 in
	namd)
		install_namd
		;;

	namdHttpd)
		install_namdHttpd
		;;

	both)
		install_both
		;;
esac


```
