<!doctype HTML>
<head>
<meta chrset="utf-8">
</head>
<body>

POST
<?php
    foreach ($_POST as $key => $value)
    {
        //echo $key." = ".$value.
        echo "<br />"; 
    }
?>

GET
<?php
    foreach ($_GET as $key => $value)
    {
        //echo $key." = ".$value.;
        echo "<br />"; 
    }
?>

REQUEST
<?php
    foreach ($_REQUEST as $key => $value)
    {
        //echo $key." = ".$value.;
        echo "<br />"; 
    }
?>
</body>