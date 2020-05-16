ttab 'socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"'
open /Applications/Utilities/xQuartz.app
CID=$(docker run -it -e DISPLAY=192.168.0.9:0 -v `pwd`:/content -d rottiakash/xcgv)
CID=${CID:0:12}
docker exec -it $CID bash
docker kill $CID