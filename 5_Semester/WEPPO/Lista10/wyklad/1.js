// autentykacja i autoryzacja

// autentykacja - proces rozpoznania tożsamości użytkownika
// logged vs not logged

// autoryzacja - proces decyzyjny w którym przydziela się dostęp do zasobu
// more based on roles, permissions etc.
// level 1 < level 2 < level 3
// but what if there are sets which should not be a subset
// example: student vs lecturer -> what if you are both -> creating two accounts?? :(

// authentication: store cookie
// type 1: store only suername
// Con: roles must be calculated by the server on every request
// Pro: we can change roles immediately
// type 2: store username + additional data (roles etc.)
// Con: can't change immediately
// Con: cookie size is limited (can't have too many roles)
// Pro: no additional cost for calculatin roles

// 401 Challenge -> corp networks (domain controller and automatic connection)
// annoying for user (login-password pop-up (which is default for given browser))

// authentication middleware
// comma-seperated middlewares
// authenication and redirect (302) to login page
// good practice scenario: returnUrl?=
// signed cookies
// logout -> age: = -1
// conditional rendering -> locals
// centering using flexbox

// authorize can return function
// maybe pass set of rules to this authorize function

// more complicated stuff -> passport

// safe infrastructure:
// 1) encrypted connection (SSL) 
// -> after logging connection should be kept secure!
// 2) storing passwords safely
// never store passwords without hashing
// rainbow table attacks (when we only hashed) 
// -> attacker uses known passwords and check if any passwords match in the db
// -> then popular password is cracked 
// salting before hashing (random, unique salt for every password)
// salt is stored explicite alongside password
// iterating hashing function (e.g. SHA256)
// P = SHA256(SHA256(SHA256(SHA256(pass + salt) + salt) + salt) + salt)
// it increases entropy massively
// choose iteration to keep it about 50-500ms
// in practice use bcrypt or PBKDF2

// multiple passwords:
// e.g. password history && security policies

// federated authentication
// service provider, identity provider
// idP authenticates user and goes back to SP
// existing SSO protocols
// passive WS-Federation (signed token passed by browser)
// OAuth2/OpenID Connect (token passed between servers)

// e.g. Login with Google
// POST can be posted to any site on the web!
// Google API - projects


