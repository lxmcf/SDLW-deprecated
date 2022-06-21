message ('Examples will build!')

examples = [
    'window',
    'callbacks'
]

foreach current_example : examples
    executable (
        current_example,

        current_example / 'main.c',

        dependencies: project_library_dependency,

        install: false
    )
endforeach
