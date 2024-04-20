g++ -O3 -Wall -shared -undefined dynamic_lookup -std=c++20 -fPIC $(python3 -m pybind11 --includes) csvpy.cpp -o csvpy$(python3-config --extension-suffix)

