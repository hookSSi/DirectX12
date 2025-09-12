set(common_sources
    src/core/common/GameTimer.cpp
)

set(sources
    src/core/tmp.cpp
    ${common_sources}
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(common_headers
    include/core/common/GameTimer.h
)

set(headers
    include/core/tmp.hpp
    ${common_headers}
)
  
set(test_sources
  src/core/tmp_test.cpp
)
