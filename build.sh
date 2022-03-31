mkdir build

cd build

mkdir unix

cd ..

cmake -G "Ninja" -B build/unix -S src
cmake --build build/unix
