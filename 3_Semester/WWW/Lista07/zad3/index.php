<?php
$IsPostFormData = (isset($_POST["sent"]) && ($_POST["sent"]=="y"));
$IsGetFormData = (isset($_GET["sent"]) && ($_GET["sent"]=="y"));
$IsRemovingFormData = (isset($_POST["removeForm"]) && $_POST["removeForm"]=="y");
$UploadDir="D:\\WWWUpload\\";
$UploadDirSub = "D:\\WWWUpload\\".date("YmdHis")."\\";
$UploadCodes = array( "UPLOAD_ERR_OK", "UPLOAD_ERR_INI_SIZE", "UPLOAD_ERR_FORM_SIZE", "UPLOAD_ERR_PARTIAL", "UPLOAD_ERR_NO_FILE" );
$MaxFileSize=10000000;
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Wysyłanie plików przez formularz</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<style type="text/css">
td,th,body { font-family:Verdana, Arial, Helvetica, sans-serif; font-size:10pt; }
</style>
</head>

<body>

<div align="center">

<h3>Wysyłanie plików przez formularz</h3>

<?php
  if( $IsRemovingFormData )
  {
    $removeFilePath = filter_input(INPUT_POST,'removeFilePath');
    $removeFileName = filter_input(INPUT_POST,'removeFileName');
    $fullPathFile = realpath($removeFilePath."\\".$removeFileName);
    if(is_file($fullPathFile) && unlink($fullPathFile))
      echo "File ".$removeFileName." on path ".$removeFilePath." deleted successfully!";
    else
      echo "Error on deleting file, path ".$removeFilePath."\\".$removeFileName." does not exist or directory is empty";
    
    echo "</br>";
   
    if(is_dir($removeFilePath) && rmdir($removeFilePath))
      echo "Directory ".$removeFilePath." deleted successfully!";
    else
      echo "Error on deleting directory, path ".$removeFilePath." does not exist.";
  }

  if ( $IsPostFormData )
  {
  mkdir( $UploadDirSub );
 ?>
 <table cellpadding="4" cellspacing="2" border="1" rules="groups">
 <?php
    $successUpload = false;
    $UploadFile = $UploadDirSub.$_FILES['plik']['name'];
	  if ( is_uploaded_file( $_FILES['plik']['tmp_name'] ) )
	  {
        if ( $_FILES['plik']['size'] > $MaxFileSize )
        { 
          echo "<td colspan=\"2\" style=\"color:green\">Plik jest za duży</td>"; 
        }
        else
        { 
  	      echo "<tbody>";
	        echo "<tr>";
  	      if ( move_uploaded_file( $_FILES['plik']['tmp_name'], $UploadFile ))
	        {
            $successUpload = true;
            echo "<td colspan=\"2\" style=\"color:green\">Plik został poprawnie uploadowany i skopiowany w nowe miejsce<br>$UploadFile</td></tr>";
          }
          else
          {
            echo "<td colspan=\"2\" style=\"color:green\">Błąd przy uploadowaniu</td>";
          }
	        echo "</tr>";
          echo "<tr><td style=\"color: navy; text-align: left\">Nazwa wysłanego pliku (po stronie klienta):</td><td>".$_FILES["plik"]["name"]."</td></tr>\n";
          echo "<tr><td style=\"color: navy; text-align: left\">Typ zawartości wysłanego pliku:</td><td>".$_FILES["plik"]["type"]."</td></tr>\n";
          echo "<tr><td style=\"color: navy; text-align: left\">Rozmiar wysłanego pliku:</td><td>".$_FILES["plik"]["size"]."</td></tr>\n";
          echo "<tr><td style=\"color: navy; text-align: left\">Nazwa pliku na serwerze:</td><td>".$_FILES["plik"]["tmp_name"]."</td></tr>\n";
          echo "<tr><td style=\"color: navy; text-align: left\">Kod błędu związany z wysłaniem pliku:</td><td>".$UploadCodes[$_FILES["plik"]["error"]].":".$_FILES["plik"]["error"]."</td></tr>\n";
	        echo "</tbody>";
        }
    }
    else
    {
      echo "Upload files via POST!";
      echo "</br>";
      echo "Or check your PHP.ini for POST-MAX";
    }
    if(!$successUpload)
    {
      rmdir($UploadDirSub);
    }
?>
</table>
<?php
  }
?>

<form action="index.php" method="post" enctype="multipart/form-data" name="plik">
<input type="hidden" name="MAX_FILE_SIZE" value="<?php echo $MaxFileSize;?>">
<table cellpadding="2" cellspacing="0" border="0" bgcolor="#00FF00">
<tr><td>Plik:</td><td><input type="file" name="plik" size="40"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" name="Submit" value="Wyślij"></td></tr>
</table>
<input type="hidden" name="sent" value="y">
</form>

<h2> Przesłane pliki: </h2>
<table cellpadding="2" cellspacing="10" border="0" bgcolor="green">
<tr> 
  <th> Lokalizacja </th>
  <th> Nazwa </th>
  <th> Usun </th>
</tr>
<?php 
  $allFiles = scandir($UploadDir);
  $savedFiles = array_diff($allFiles, array('.', '..'));
  foreach($savedFiles as $file)
  {
    $subfiles = scandir(realpath($UploadDir.$file));
    $name = join(array_diff($subfiles, array('.', '..')));
    $filepath = realpath($UploadDir.$file."\\");
    echo "<tr><td>".$filepath."</td><td>".$name."</td>";
    ?>
    <td>
    <form action='index.php' method='post' class='remove'>
      <input type='submit' value='Usuń'>
      <input type='hidden' name='removeFilePath' value ='<?php echo $filepath; ?>'>
      <input type='hidden' name='removeFileName' value ='<?php echo $name; ?>'>
      <input type='hidden' name='removeForm' value='y'>
    </form>
    </td>
    </tr>
    <?php
  }
?>
</table>
</div>

</body>
</html>
