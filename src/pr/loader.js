function compatibility() {
    const replace = [ ["##X", "#X"], ["#%23X", "#X"], ["##", "#!"], ["#%23", "#!"] ];

    for(const [key, val] of replace) {
        if(window.location.hash.startsWith(key)) {
            window.location.hash = val + window.location.hash.substr(key.length);
            window.location.reload(true);
        }
    }
}

export function decodeTarget() {
    compatibility();

    const hash = window.location.hash;

    if(hash.startsWith("#X")) {
        return new URL(`/ref/${hash.substr(2)}`, window.location.href);
    }

    if(hash.startsWith("#!")) {
        return new URL(`/so/${hash.substr(2)}`, window.location.href);        
    }

    return new URL(hash.substr(1));
}

export function getSource(url) {
    const headers = new Headers();
    headers.append("Accept", "text/plain");

    const request = new Request(url, {
        method: "GET",
        cache: "no-cache",
        headers
    });

    return fetch(request).then(response => {
      if(response.status == 404) {
        throw 404;
      }

      return response.text();
    });
}

