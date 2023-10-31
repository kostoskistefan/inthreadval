project(
    'inthreadval',
    'c',
    version: '1.0.0',
    license: 'MIT'
)

buildtype = 'release'

install_headers('include/inthreadval.h')

inthreadval_sources = [
    'source/inthreadval.c'
]

inthreadval_lib = shared_library(
    'inthreadval',
    inthreadval_sources,
    dependencies: dependency('threads'),
    install: true
)

inthreadval_dep = declare_dependency(link_with: inthreadval_lib)

pkg = import('pkgconfig')
pkg.generate(inthreadval_lib)
