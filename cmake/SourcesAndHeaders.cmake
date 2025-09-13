set(common_sources
    src/core/common/d3dApp.cpp
    src/core/common/d3dUtil.cpp
    src/core/common/DDSTextureLoader.cpp
    src/core/common/GameTimer.cpp
    src/core/common/MathHelper.cpp
)

set(sources
    ${common_sources}
    src/core/AppInitializer.cpp
)

set(exe_sources
    ${sources}
    src/main.cpp
)

set(common_headers
    include/core/common/d3dApp.h
    include/core/common/d3dUtil.h
    include/core/common/d3dx12.h
    include/core/common/DDSTextureLoader.h
    include/core/common/GameTimer.h
    include/core/common/MathHelper.h
)

set(headers
    ${common_headers}
    include/core/AppInitializer.h
)
  
# set(test_sources

# )
