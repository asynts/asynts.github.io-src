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
      console.log(PR);
      PR.prettyPrint();
    }).catch(err => err.innerText = err);
} else {
  welcome.hidden = false;
}
