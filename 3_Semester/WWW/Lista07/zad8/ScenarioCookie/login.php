<!--source: https://stackoverflow.com/questions/19531044/creating-a-very-simple-1-username-password-login-in-php -->

<?php
// config PHP.ini
//session.use_strict_mode=0 (default 0)
//"session.use_cookies",1 (default 1)
//"session.use_trans_sid",1 (default 0)
//"session.use_only_cookies=0 (default 1)

$username = ((isset($_POST["username"])) ? htmlspecialchars($_POST["username"]) : "");
$errorMsg = "";

if(isset($_GET['session_id']))
{
    session_id($_GET['session_id']);
}
else
    session_start();

if(!isset($_SESSION["login"]))
  $_SESSION["login"] = false;

$validUser = $_SESSION["login"] === true;
if(isset($_POST["sub"])) {
  $validUser = $_POST["username"] == "admin" && $_POST["password"] == "password";
  if(!$validUser) $errorMsg = "Invalid username or password.";
  else $_SESSION["login"] = true;
}
if($validUser) {
  header("Location: ./login-success.php"); 
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
  <form name="input" action="" method="post">
    <label for="username">Username:</label><input type="text" value="<?php echo $username; ?>" id="username" name="username" />
    <label for="password">Password:</label><input type="password" value="" id="password" name="password" />
    <div class="error"><?php echo $errorMsg; ?></div>
    <input type="submit" value="Login" name="sub" />
  </form>
</body>