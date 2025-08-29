dir = include_directories('.')

fossil_sys_lib = library('fossil_sys',
    files('memory.c', 'datetime.c', 'hostinfo.c', 'syscall.c', 'bitwise.c'),
    install: true,
    dependencies: [dependency('threads')],
    include_directories: dir)

fossil_sys_dep = declare_dependency(
    link_with: [fossil_sys_lib],
    dependencies: [dependency('threads')],
    include_directories: dir)
