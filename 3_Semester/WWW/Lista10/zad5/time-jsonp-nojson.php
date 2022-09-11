<?php
header("Cache-Control: max-age=-1");
$d = getdate();
$functionCall = preg_match("/^\w+$/", $_REQUEST["callback"])==1 ? $_REQUEST["callback"] : "functionCall";
echo "$functionCall(".$d['hours'].":".$d['minutes'].":".$d['seconds'].", ".$d['mday'].".".$d['mon'].".".$d['year'].")";
?>