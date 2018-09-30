let obj = {
  a: function() {
    // let's use a timeout for simplicity
    setTimeout(this.b, 100);
  },

  b: function() {
    console.log(this);
  }
};

obj.a();
