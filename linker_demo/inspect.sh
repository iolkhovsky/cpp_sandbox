#/bin/bash
echo "readelf"
echo ""
readelf -h app
readelf -d app | grep NEEDED
echo ""
echo "ldd (app)"
echo ""
ldd app
echo ""
echo "ldd (lib)"
echo ""
ldd libcustomops.so
