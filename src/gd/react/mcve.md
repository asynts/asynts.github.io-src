---
title: creating a good example involving react
layout: guide
---

React projects often require a huge setup, involving tools like babel or webpack. When asking questions
on sites like [Stack Overflow][1] you are faced with a problem:

1. You can't provide all your code, because nobody reads through your 500+ line project.
2. You can't provide an excerpt, because that forces the responding to take a guess (he won't be
   be able to try it out).

The objective of this guide is to help you create a few lines of code that can reproduce your problem (see [MCVE][2]).
Start by narrowing down the problem; try commenting out, or deleting code from your exising codebase.

When you know what code causes the problem, you can put it into an environment like shown below:

```html
<script src="https://unpkg.com/react@16/umd/react.development.js" crossorigin></script>
<script src="https://unpkg.com/react-dom@16/umd/react-dom.development.js" crossorigin></script>

<div id="target"></div>

<script>
  const e = React.createElement;

  // code goes here

  const component = e("h1", null, "Hello, World!");
  ReactDOM.render(component, document.getElementById("target"));
</script>
```

The comment marks the location where you can place your code. You probably need to adapt your code,
it needs to run without errors! (unless that is the problem)

*Note: Stack Overflow has a feature called [snippets][3], use them if you can!*

*Note: [Here][4] is a complete example hostet on jsfiddle.*

  [1]: https://stackoverflow.com/
  [2]: https://stackoverflow.com/help/mcve
  [3]: https://meta.stackoverflow.com/a/358993/8746648
  [4]: https://jsfiddle.net/asynts/pxqs2c56/
