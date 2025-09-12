# 의존성

(setup-cpp)[https://github.com/aminya/setup-cpp] 을 사용하여 의존성 설치

다음은 예시

```shell
curl -LJO "https://github.com/aminya/setup-cpp/releases/download/v0.5.7/setup_cpp_windows.exe"
./setup_cpp_windows --compiler llvm --cmake true --ninja true --ccache true --cppcheck true
```

# 빌드

```shell

cmake -G Ninja -S . -B ./build

cmake --build ./build

```

# 테스트
```shell
ctest -C Debug --test-dir ./build/test/
```

# 빌드 타겟 파일들 설정

`cmake/SourcesAndHeaders.cmake` 파일 수정