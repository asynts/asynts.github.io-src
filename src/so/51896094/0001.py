#!/usr/bin/env python3

# run this script and then run the following bash command:
# $ curl -H "Content-type: application/json" -X POST http://127.0.0.1:5000/book_room -d '{"4":{"room":"602","date":"2 days ago","booked_by":"HR"}} '

import json
from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
  def do_POST(self):
    length = int(self.headers["Content-Length"])
    data = self.rfile.read(length)

    print(json.loads(data)) # reassure valid json 

HTTPServer(("", 5000), RequestHandler).serve_forever()
