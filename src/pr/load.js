export default function() {
  const output = document.getElementById("output");
  const welcome = document.getElementById("welcome");
  const error = document.getElementById("error");

  if(window.location.hash.length == 0) {
    welcome.hidden = false;
    return;
  }

  const params = new URLSearchParams(window.location.search);

  let url = window.location.hash.substr(1);

  // provide some abbreviations
  if(url.startsWith("#X")) {
    url = `../ref/${url.substr(2)}`;
  } else if(url.startsWith("#")) {
    url = `../so/${url.substr(1)}`;
  }

  const lang = params.get("lang");
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
}

