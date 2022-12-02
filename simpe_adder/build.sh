#/usr/bin

echo "Building..."
g++ -std=c++17 main.cpp -o app
echo "Running..."
./app 10240 20
echo "Done"
