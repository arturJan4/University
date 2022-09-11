<?php
header("Cache-Control: max-age=-1");
header("Access-Control-Allow-Origin: http://wroclawski.eu");
$d = getdate(); 
echo $d['hours'].":".$d['minutes'].":".$d['seconds'].", ".$d['mday'].".".$d['mon'].".".$d['year']."<br/>";
foreach($_SERVER as $key => $value)
	echo $key."=".$value."<br/>";
?>