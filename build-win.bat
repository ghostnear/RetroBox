mkdir build

pushd build
mkdir windows
popd

cmake -G "Ninja" -B build/windows/ -S src
cmake --build build/windows