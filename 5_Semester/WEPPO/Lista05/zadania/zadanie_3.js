var http = require("http");
var res_filename = 'txt_resp.txt';

var server =
  http.createServer(
    (req, res) => {
      res.setHeader("Content-Disposition", `attachment; filename=${res_filename}`)
      res.write("This is a response generated using Content-Disposition.\n");
      res.end("can also write in res.end() here!");
    });
server.listen(8000);
console.log("started the server");