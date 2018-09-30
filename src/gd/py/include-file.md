---
title: embedding files in python scripts
layout: guide
---

This guide is supposed to help you create a minimal, complete, and verifiable example without additional setup. The following
examples should be what you have now:

```py
with open("data.csv") as f:
  # ...
```

... or ...

```py
f = open("data.csv")
# ...
f.close()
```

The code above can't stand on it's own. It depends on the `data.csv` file which other people won't have on their computers.
Many people would tend to attach the file to the question, but often there is a better solution. You can embed the file into you python script:

```py
import io

# notice the backslash before the newline
f = io.StringIO("""\
FILE CONTENT HERE
""")

# ...
```

This won't work in every senario, if your file is huge or containes binary data it might not be a good idea to embed it. *(note: your file shouldn't be huge!)*
