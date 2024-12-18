
# cmakeに要求する最低バージョン
cmake_minimum_required(VERSION 3.00)

# プロジェクト名
project(StopWatch)

# 出力するバイナリ
add_library(StopWatchLib STATIC)

# C++20を使用する
set_target_properties(${TARGET_NAME}
	PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
)

# ソースファイル
target_sources(StopWatchLib
	PRIVATE
		stop_watch.h
		stop_watch.cpp
)

# 公開するインクルードディレクトリ
target_include_directories(StopWatchLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


## 動作確認用
add_executable(StopWatchTest)

target_sources(StopWatchTest
	PRIVATE
		main.cpp
)

target_link_libraries(StopWatchTest PRIVATE StopWatchLib)
