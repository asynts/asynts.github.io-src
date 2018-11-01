function func() {
  console.log("func called");
}

console.log("1.");
{ func }

console.log("2.");
{ func() } // func called

console.log("3.");
{() => func}

console.log("4.");
{() => func()}

