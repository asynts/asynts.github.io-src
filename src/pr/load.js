function decodeTarget() {
  let hash = window.location.hash;

  // '#' isn't allowed to appear in a uri fragment
  if(hash.startsWith("##X")) {
    window.location.hash = hash.substr(1);
    window.location.reload();
  }

  if(hash.startsWith("#X")) {
    return `../ref/${hash.substr(2)}`;
  }

  if(hash.startsWith("#!")) {
    return `../so/${hash.substr(2)}`;
  }

  console.error(`unknown target: ${hash.substr(1)}`);
  return hash.substr(1);
}

export default function() {
  const output = document.getElementById("output");
  const welcome = document.getElementById("welcome");

  if(window.location.hash.length == 0) {
    welcome.hidden = false;
    return;
  }

  let url = new URL(decodeTarget(), window.location.href);
  url.hash = "";

  const lang = new URLSearchParams(window.location.search).get("lang");

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

