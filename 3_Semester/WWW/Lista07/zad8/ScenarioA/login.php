<!--form source: https://stackoverflow.com/questions/19531044/creating-a-very-simple-1-username-password-login-in-php -->

<?php
// w php.ini
//session.use_strict_mode=0 (default 0) // server generates SSID
//"session.use_cookies",0 (default 1)
//"session.use_trans_sid",1 (default 0)
//"session.use_only_cookies=0 (default 1)

// Wariant 1: A simple attack scenario
/*
A wysyła B URL z fixowanym SID, np: domena.php?=SESSID=whatever
B otwiera stronę i loguje się (na tej sesji!)
A wpisuje stronę domena.php?=SESSID=whatever i jest w tej samej sesji zalogowany
*/
// Wariant 2: Attack using server generated SID
/*
#Serwer blokuje SID wygenerowane przez użytkownika#
A pobiera URL i sprawdza przypisane mu SID np: SESSID=f23929dfksd92he
A wysyła B URL z fixowanym SID, np: domena.php?=SESSID=f23929dfksd92he
B otwiera stronę i loguje się (na tej sesji!)
A wpisuje stronę domena.php?=SESSID=f23929dfksd92he i jest w tej samej sesji zalogowany
*/
$username = ((isset($_POST["username"])) ? htmlspecialchars($_POST["username"]) : "");
$errorMsg = "";

session_start();

$pathWithSession = "login.php?".SID;
echo "SID= ".$pathWithSession;
if(!isset($_SESSION["login"]))
  $_SESSION["login"] = false;

$validUser = $_SESSION["login"] === true;
if(isset($_POST["sub"])) {
  $validUser = $_POST["username"] == "admin" && $_POST["password"] == "password";
  //if($validUser) session_regenerate_id();
  if(!$validUser) $errorMsg = "Invalid username or password.";
  else $_SESSION["login"] = true;
}
if($validUser) {
  header("Location: ./login-success.php?".SID); 
  die();
}
?>
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html;charset=utf-8" />
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <title>Login</title>
</head>
<body>
  <form name="input" action="<?php echo $pathWithSession;?>" method="post">
    <label for="username">Username:</label><input type="text" value="<?php echo $username; ?>" id="username" name="username" />
    <label for="password">Password:</label><input type="password" value="" id="password" name="password" />
    <div class="error"><?php echo $errorMsg; ?></div>
    <input type="submit" value="Login" name="sub" />
  </form>
</body>