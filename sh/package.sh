if [ ! -d "/final" ]; then
  mkdir /final
fi
 
mkdir /final/cfg/
mkdir /final/lib/

cp ./fa/exe ./final/
cp ./fa/cfg/*.* ./final/cfg/
cp ./fa/lib/*.* ./final/lib/

tar zcvf fa.tar.gz ./final
