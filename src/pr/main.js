import {decodeTarget, getSource} from "./loader.js";

// some browsers don't refresh if only the fragment changed
const prev = window.location.hash;
setInterval(() => {
    if(prev != window.location.hash) {
        window.location.reload(true);
    }
}, 500);

document.body.onload = () => {
    if(window.location.hash.length == 0) {
        document.getElementById("welcome").hidden = false;
        return;
    }

    const outputElem = document.getElementById("output");
    const lang = new URLSearchParams(window.location.search).get("lang");

    getSource(decodeTarget(), source => {
        outputElem.innerHTML = PR.prettyPrintOne(source, lang)
    });
};
