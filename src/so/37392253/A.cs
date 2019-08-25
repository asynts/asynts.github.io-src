class A
{
  int x {
    get;
    set {
      // ...

      /* ??? */ = value; // here is the issue
    }
  }
}

