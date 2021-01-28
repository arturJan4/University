<?php 
    if(isset($_GET['session_id']))
    {
        session_id($_GET['session_id']);
    }
    else
        session_start();
?>

<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="content-type" content="text/html;charset=utf-8" />
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <title>Login</title>
</head>
<body>
    <?php 
        echo "SID= ".SID."<br>";
        if(isset($_SESSION["login"]) && $_SESSION["login"] === true)
            echo "Strona tylko dla zalogowanych użytkowników";
        else
            echo "Nie jesteś zalogowany";
    ?>
</body>