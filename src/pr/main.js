const output = document.getElementById("output");
const welcome = document.getElementById("welcome");
const error = document.getElementById("error");

const params = new URLSearchParams(window.location.search);

if(window.location.hash.length > 0) {
  let url = window.location.hash.substr(1);
  const lang = params.get("lang");

  if(url.startsWith("#")) {
    url = `../so/${url.substr(1)}`;
  }

  if(lang !== null) {
    output.classList.add(`lang-${lang}`);
  }

  const headers = new Headers();
  headers.append("Accept", "text/plain");

  const request = new Request(url, {
    method: "GET",
    cache: "no-cache",
    headers
  });

  fetch(request)
    .then(response => response.text())
    .then(text => {
      output.innerText = text;
      output.classList.remove("prettyprinted");
      PR.prettyPrint();
    }).catch(err => err.innerText = err);
} else {
  welcome.hidden = false;
}

const urlin = document.getElementById("url-in");
const urlout = document.getElementById("url-out");

function update() {
  let url = urlin.value;

  if(url.startsWith("https://raw.githubusercontent.com/asynts/stack-overflow/master/")) {
    url = url.replace("https://raw.githubusercontent.com/asynts/stack-overflow/master/", "#");
  } else if(url.startsWith("https://asynts.github.io/so/")) {
    url = url.replace("https://asynts.github.io/so/", "#");
  }

  url = window.location.protocol + "//" + window.location.host + "/pr/#" + url;

  urlout.innerText = url;
  urlout.href = url;
}

urlin.onkeyup = update;
update();

