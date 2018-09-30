new Promise(() => {
  // promises aren't executed asynchronously, this will still block
  while (true) { }
});

// won't be executed because the promise blocks
setInterval(() => console.log("."), 100);
