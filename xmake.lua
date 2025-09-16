add_rules("mode.debug", "mode.release")

add_repositories("groupmountain-repo https://github.com/GroupMountain/xmake-repo.git")

add_requires(
    "binarystream 2.3.2",
    "pybind11-cibw 3.0.1"
)

if is_plat("windows") and not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("_bstream")
    set_languages("c++23")
    set_kind("shared")
    set_targetdir("./build/bin")
    set_prefixname("")
    set_extension("")
    add_packages(
        "pybind11-cibw",
        "binarystream"
    )
    add_defines("PYBIND11_PYTHON_VERSION=0x03080000")
    on_load(function (target)
        local include = os.iorun("python -c \"import sysconfig; print(sysconfig.get_path('include'))\""):sub(1, -2)
        local lib = os.iorun("python -c \"import sysconfig; print(sysconfig.get_config_var('LIBDIR') or sysconfig.get_config_var('LIBPL'))\""):sub(1, -2)
        if is_plat("windows") then 
            lib = os.iorun("python -c \"import sysconfig; print(sysconfig.get_config_var('installed_base') + '\\libs')\""):sub(1, -2)
        end
        local version = os.iorun("python --version"):sub(1, -2)
        target:add("includedirs", include)
        target:add("linkdirs", lib)
        cprint("${bright green}[Python]:${reset} include: " .. include)
        cprint("${bright green}[Python]:${reset} lib: " .. lib)
        cprint("${bright green}[Python]:${reset} version: " .. version)
    end)
    add_files("bindings/**.cpp")
    if is_plat("windows") then
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
        add_cxflags(
            "-Wall",
            "-pedantic",
            "-fexceptions",
            "-fPIC",
            "-O3",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden"
        )
        add_shflags("-static-libstdc++")

        if is_plat("linux") then 
            add_shflags("-static-libgcc")
        end
        if is_plat("macosx") then
            add_mxflags("-target arm64-apple-macos11.0", "-mmacosx-version-min=11.0")
            add_ldflags("-target arm64-apple-macos11.0", "-mmacosx-version-min=11.0")
            add_shflags("-target arm64-apple-macos11.0", "-mmacosx-version-min=11.0")
        end
    end
