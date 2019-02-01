import load from "./load.js"

let urlin, urlout;

function abbreviateUrl(url, full, abb) {
  if(url.startsWith(full)) {
    return url.replace(full, abb);
  }

  return url;
}

function update() {
  let url = urlin.value;

  url = abbreviateUrl(url, "https://raw.githubusercontent.com/asynts/stack-overflow/master/", "#");
  url = abbreviateUrl(url, `${window.location.protocol}//${window.location.host}/so/`, "#");
  url = abbreviateUrl(url, `${window.location.protocol}//${window.location.host}/ref/`, "#X");

  url = window.location.protocol + "//" + window.location.host + "/pr/#" + url;

  urlout.innerText = url;
  urlout.href = url;
}

document.body.onload = () => {
  load();

  // firefox won't reload if only the fragment changed
  const frag = window.location.hash;
  setInterval(() => {
    if(frag != window.location.hash) {
      window.location.reload();
    }
  }, 500);

  urlin = document.getElementById("url-in");
  urlout = document.getElementById("url-out");

  urlin.onkeyup = update;
  update();
};

