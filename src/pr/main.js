import {decodeTarget, getSource} from "./loader.js";

function abbreviate(url) {
    const replace = [
        ["https://raw.githubusercontent.com/asynts/stack-overflow/master/", "!"],
        [new URL("/so/", window.location.href).href, "!"],
        [new URL("/ref/", window.location.href).href, "X"]
    ];

    for(const [key, val] of replace) {
        if(url.startsWith(key)) {
            return val + url.substr(key.length);
        }
    }

    return url;
}

function updateWelcome() {
    const urlinElem = document.getElementById("urlin");
    const urloutElem = document.getElementById("urlout");

    let url = new URL(window.location.href);
    url.hash = "#" + abbreviate(urlinElem.value.trim());

    urloutElem.innerText = url.href;
    urloutElem.href = url.href;
}

document.body.onload = () => {
    if(window.location.hash.length == 0) {
        document.getElementById("welcome").hidden = false;
        document.getElementById("urlin").onkeyup = updateWelcome;
        updateWelcome();
        return;
    }

    const outputElem = document.getElementById("output");
    const lang = new URLSearchParams(window.location.search).get("lang");

    getSource(decodeTarget())
      .then(source => {
        outputElem.innerText = source;
        outputElem.innerHTML = PR.prettyPrintOne(outputElem.innerHTML, lang)
      }).catch(err => {
        if(err == 404) {
          document.getElementById("error").hidden = false;
          return;
        }

        throw err;
      });
};

// some browsers don't refresh if only the fragment changed
const prev = window.location.hash;
setInterval(() => {
    if(prev != window.location.hash) {
        window.location.reload(true);
    }
}, 500);

