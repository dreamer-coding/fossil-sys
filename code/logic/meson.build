dir = include_directories('.')
add_project_arguments('-D_POSIX_C_SOURCE=200112L', language: 'c')
add_project_arguments('-D_POSIX_C_SOURCE=200112L', language: 'cpp')

fossil_sys_lib = library('fossil_sys',
    files(
        'memory.c',
        'hostinfo.c',
        'syscall.c',
        'dynamic.c',
        'process.c',
        'bitwise.c',
        'event.c',
        'device.c',
        'os.c'),
    install: true,
    dependencies: [dependency('threads')],
    include_directories: dir)

fossil_sys_dep = declare_dependency(
    link_with: [fossil_sys_lib],
    dependencies: [dependency('threads')],
    include_directories: dir)

meson.override_dependency('fossil-sys', fossil_sys_dep)