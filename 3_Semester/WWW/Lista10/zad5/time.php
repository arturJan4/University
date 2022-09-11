<?php
header( "Cache-Control: max-age=-1" );
$d = getdate(); 
echo $d['hours'].":".$d['minutes'].":".$d['seconds'].", ".$d['mday'].".".$d['mon'].".".$d['year'];
?>