# 빌드

```shell

cmake -S . -B ./build

cmake --build ./build

```

# 테스트
```shell
ctest -C Debug --test-dir ./build/test/
```

# 빌드 타겟 파일들 설정

`cmake/SourcesAndHeaders.cmake` 파일 수정