import io

# notice the backslash before newline
f = io.StringIO("""\
CSV CONTENT HERE
""")

# f can now be treated like a file opened with `open()`
