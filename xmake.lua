add_rules("mode.debug", "mode.release")

add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires(
    "binarystream 2.3.1",
    "pybind11 3.0.1"
)

if is_plat("windows") then
    if not has_config("vs_runtime") then
        set_runtimes("MD")
    end
    set_extension(".pyd")
    add_defines(
        "NOMINMAX",
        "UNICODE"
    )
    add_cxflags(
        "/EHsc",
        "/utf-8",
        "/W4",
        "/O2",
        "/Ob3"
    )
else
    set_toolchains("clang")
    set_extension(".so")
    add_cxflags(
        "-Wall",
        "-pedantic",
        "-fexceptions",
        "-stdlib=libc++",
        "-fPIC",
        "-O3",
        "-fvisibility=hidden",
        "-fvisibility-inlines-hidden"
    )
    add_shflags(
        "-stdlib=libc++",
        "-static-libstdc++",
        "-static-libgcc"
    )
    add_syslinks("libc++.a", "libc++abi.a")       
end

add_packages(
    "pybind11",
    "binarystream"
)
set_targetdir("./build/bin")
set_prefixname("")
set_languages("cxx23")
set_kind("shared")

target("_bstream")
    add_files("bindings/bstream.cpp")