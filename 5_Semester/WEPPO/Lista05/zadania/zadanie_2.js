var fs = require("fs");
var https = require("https");

(async function () {
  var pfx_cert = await fs.promises.readFile("5/zadania/cert.pfx");
  var server = https.createServer({
    pfx: pfx_cert,
    passphrase: "admin"
  },
    (_, res) => {
      res.setHeader("Content-type", "text/html; charset=utf-8");
      res.end("page with a certificate");
    });
  server.listen(8000);
  console.log("started the server");
})();