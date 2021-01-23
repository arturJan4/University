<!doctype HTML>
<head>
<meta chrset="utf-8">
</head>
<body>
<h1>Nagłówki</h1>

<?php

	foreach (getallheaders() as $name => $value) {
		echo "$name: $value\n";
}

?>
<h1>Zmienne POST</h1>
<?php
    foreach ($_POST as $key => $value)
        echo $key.'='.$value.'<br />';
?>

<h1> Zmienne GET</h1>
<?php
    foreach ($_GET as $key => $value)
        echo $key.'='.$value.'<br />';
?>

<h1> Zmienne REQUEST</h1>
<?php
    foreach ($_REQUEST as $key => $value)
        echo $key.'='.$value.'<br />';
?>
</body>