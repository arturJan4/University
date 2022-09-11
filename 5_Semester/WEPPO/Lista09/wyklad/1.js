// ngrok -> publicize (duplex channel) url
// testing on mobile, by sb else etc.

// strong typing in VSCode
// JSDoc
// ECMAScript 6 modules
// require -> import * as http from "http"
// package.json: commonjs -> module

// default middleware routing
// app.use(...)
// 404.ejs example

// cross-site scripting
// percent encoding (<%= %>)
// without decoding and additionaly decode passed:
// <%- decodeURIComponent(url) %>

// parameters in path
/*
app.get("/faktura/:id",
  (req, res) => { res.end(`dynamicznie generowana faktura:
${req.params.id}`)});
*/
// can use regex
// app.get("/faktura/:id(\\d+)", ...

// web parameter tampering
// example: id is an id of a database
// user can use without logging in
// then it is easy to guess next, prev id
// and steal data
// solution 1: use GUID 2^128 -> make it long enough
// solution 2: HMAC
// additional parameter: HMAC (Hash Message Authentication Code)
// binding id with private key
// SHA2
// wrong approach (because sha256 is rather irreversible)
// id -> sha256(id) -> long hash (and we pass hash -> but how to reverse it?)
// wrong 2: pass both -> then attacker can use sha
// correct: we have a private key and we concatonate it with id
// server gets a request -> server sees id, hash and has a private key
// checks if the sha(id+key) and hash it got match

// cookies
// cookie-parser
// stateless HTTP
// tracking cookies
// max cookie size: 4kB
// max cookies: ~X00 (on popular browsers)
// req -> incoming cookies
// res -> outgoing cookies
// set-cookie header
// expires/maxAge
// signed -> HMAC
// deleting -> maxAge = -1
// httpOnly -> can not be managed by javascript (security)
// client doesn't use it

// cookie tampering
// signed -> HMAC
// authentication of user!

// efficiency -> session container server-side
// express-session
// memory or db (redis etc.)

// session hijacking
// entropy + signing

// complex templates with parameters

