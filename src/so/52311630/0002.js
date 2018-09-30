let obj = {
  a: function() {
    // bind 'this' explicitly
    setTimeout(this.b.bind(this), 100);
  },

  b: function() {
    console.log(this);
  }
};

obj.a();
