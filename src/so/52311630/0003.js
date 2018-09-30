let obj = {
  a: function() {
    // use an arrow function
    setTimeout(() => this.b(), 100);
  },

  b: function() {
    console.log(this);
  }
};

obj.a();
