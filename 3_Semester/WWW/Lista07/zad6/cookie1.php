<?php
 setcookie( "sernik" , "z czekoladą", "/"); // root, session,
 //setcookie( "sernik" , "z czekoladą", time()+3600, "/"); // root, persistent
 setcookie( "sernik" , "z rodzynkami", time()+3600, "/Lista7/zad6/cookies", false);

// path
/*
The path on the server in which the cookie will be available on. 
If set to '/', the cookie will be available within the entire domain. 
If set to '/foo/', the cookie will only be available within the /foo/ directory and all sub-directories such as /foo/bar/ of domain. 
The default value is the current directory that the cookie is being set in.
*/
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Ciasteczka</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<style type="text/css">
td,th,body { font-family:Verdana, Arial, Helvetica, sans-serif; font-size:10pt; }
</style>
</head>

<body>

<h3>Wartość ciastka</h3>

Ciasteczko: <?php echo $_COOKIE["sernik"]; ?>
<br><a href="./cookies/index.php">Link</a>
</body>
</html>
