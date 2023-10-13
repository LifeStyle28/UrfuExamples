# Сборка

* ```conan install .. --build=missing -s compiler.libcxx=libstdc++11 -s build_type=Release && cmake .. -DCMAKE_BUILD_TYPE=Release```