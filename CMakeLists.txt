cmake_minimum_required(VERSION 3.16)

project(RayTracer)
set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracer "main.cpp" "stb_image_write.h" "pch.h" "vec3.h" "ray.h")
target_precompile_headers(RayTracer PRIVATE pch.h)
