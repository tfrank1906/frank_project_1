project('processTree', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['warning_level=3', 'werror=true'])

 thread_dep = dependency('threads')

inc_dir = include_directories('include')

src = ['src/main.cpp']
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')
add_global_arguments('-I' + get_option('fmt_include_dir'), language : 'cpp')
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')
executable('processTree',
            sources : src,     
            dependencies : thread_dep,
            include_directories: inc_dir
           )



