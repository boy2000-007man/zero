#!/bin/bash -e
check_data='action=check_online'
res=`curl -d $check_data -s http://net.tsinghua.edu.cn/cgi-bin/do_login`
if [ -z $res ]; then
    echo -1
else
    flux=`echo $res | awk -F ',' '{print $3}'`
    GB=$(($flux/1000000000))
    echo $GB | tee ~/.conky/tunet.flux
fi
exit 0
