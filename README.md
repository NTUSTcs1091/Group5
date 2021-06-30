## Requirements
Boost 1.76.0  
OpenSSL  
## Compile project and run test under ubuntu 20.04.
```
sudo apt-get update 
sudo apt install g++
sudo apt-get install -y libssl-dev

# compile gtest
# https://zwarrior.medium.com/install-google-test-framework-gtest-on-ubuntu-20-04-368eb6951b12
sudo apt-get install -y libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp ./lib/libgtest*.a /usr/lib

# compile boost library
# Finally download github repo, and compile library locally.
# https://www.boost.org/doc/libs/1_76_0/more/getting_started/unix-variants.html
# sudo apt-get install -y libboost-all-dev
# sudo wget https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2

# Boost_NO_BOOST_CMAKE=ON set this flag for cmake correctly.
sudo cmake -DCMAKE_CXX_COMPILER="g++" -DBoost_NO_BOOST_CMAKE=ON -S . -B build-wsl/
cd build-wsl/
sudo cmake --build .
ctest -V
```
