<?php
    $cardNumber = ((isset($_POST["cardNumber"])) ? array_map('htmlspecialchars', $_POST["cardNumber"]) : array("","","",""));
    $expDate = ((isset($_POST["expDate"])) ? array_map('htmlspecialchars', $_POST["expDate"]) : array("",""));
    $cvcNumber = ((isset($_POST["cvcNumber"])) ? htmlspecialchars($_POST["cvcNumber"]) : "");
    $name = ((isset($_POST["name"])) ? htmlspecialchars($_POST["name"]) : "");
    $surname = ((isset($_POST["surname"])) ? htmlspecialchars($_POST["surname"]) : "");
    $email = ((isset($_POST["email"])) ? htmlspecialchars($_POST["email"]) : "");
    $phoneNumber = ((isset($_POST["phoneNumber"])) ? htmlspecialchars($_POST["phoneNumber"]) : "");
    $ammount = ((isset($_POST["ammount"])) ? htmlspecialchars($_POST["ammount"]) : "");
?>

<?php
$IsPostFormData = (isset($_POST["sent"]) && ($_POST["sent"]=="y"));
$IsGetFormData = (isset($_GET["sent"]) && ($_GET["sent"]=="y"));
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Płatność kartą</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<style type="text/css">
td,th,body { font-family:Verdana, Arial, Helvetica, sans-serif; font-size:10pt; }
</style>
</head>

<body>

<h3 align="center">Dane karty kredytowej</h3>

<form name="dane" action="results.php" method="post">

<table align="center" cellpadding="4" cellspacing="2" border="0" bgcolor="#FF9900">
<tr>
    <th align="left">Nr karty:</th>
    <td>
        <input name="cardNumber[]" type="text" size="4" maxlength="4" value="<?php echo $cardNumber[0]; ?>" placeholder="XXXX">-
        <input name="cardNumber[]" type="text" size="4" maxlength="4" value="<?php echo $cardNumber[1]; ?>" placeholder="XXXX">-
        <input name="cardNumber[]" type="text" size="4" maxlength="4" value="<?php echo $cardNumber[2]; ?>" placeholder="XXXX">-
        <input name="cardNumber[]" type="text" size="4" maxlength="4" value="<?php echo $cardNumber[3]; ?>" placeholder="XXXX">
        <br><?php if(isset($cardNumber_error)) { echo $cardNumber_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Data ważności karty:</th>
    <td><input name="expDate[]" type="text" size="2" maxlength="2" value="<?php echo $expDate[0]; ?>" placeholder="XX">/
        <input name="expDate[]" type="text" size="2" maxlength="2" value="<?php echo $expDate[1]; ?>" placeholder="XX">
        <br><?php if(isset($expDate_error)) { echo $expDate_error; } ?>
        </td>
</tr>                            
<tr>
    <th align="left">Numer CVC:</th>
    <td><input name="cvcNumber" type="text" size="3" maxlength="3" value="<?php echo $cvcNumber; ?>" placeholder="XXX">
        <br><?php if(isset($cvcNumber_error)) { echo $cvcNumber_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Imię:</th>
    <td><input name="name" type="text" size="25" maxlength="25" value="<?php echo $name; ?>">
        <br><?php if(isset($name_error)) { echo $name_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Nazwisko:</th>
    <td><input name="surname" type="text" size="25" value="<?php echo $surname; ?>">
        <br><?php if(isset($surname_error)) { echo $surname_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Adres email:</th>
    <td><input name="email" type="email" size="25" value="<?php echo $email; ?>">
        <br><?php if(isset($email_error)) { echo $email_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Numer telefonu:</th>
    <td><input name="phoneNumber" type="text" size="11" maxlength="11" value="<?php echo $phoneNumber; ?>" placeholder="XXX XXX XXX">
        <br><?php if(isset($phoneNumber_error)) { echo $phoneNumber_error; } ?>
    </td>
</tr>
<tr>
    <th align="left">Kwota:</th>
    <td><input name="ammount" type="text" size="25" value="<?php echo $ammount; ?>" placeholder="123.45">
        <br><?php if(isset($ammount_error)) { echo $ammount_error; } ?>
    </td>
</tr>								   
<tr>
    <td align="right" colspan="2"><input type="submit" value="Wyślij"></td>
</tr>
</table>
<input name="sent" type="hidden" value="y">
</form>

<?php
if ( $IsPostFormData ):
?>
<table cellpadding="4" cellspacing="2" border="1" align="center">
<tr><th>Nr Karty:</th><td><?php echo join($cardNumber,'-'); ?></td></tr>
<tr><th>Data waznosci:</th><td><?php echo join($expDate,'/'); ?></td></tr>
<tr><th>CVC:</th><td><?php echo $cvcNumber; ?></td></tr>
<tr><th>Imie:</th><td><?php echo $name; ?></td></tr>
<tr><th>Nazwisko:</th><td><?php echo $surname; ?></td></tr>
<tr><th>Email:</th><td><?php echo $email; ?></td></tr>
<tr><th>Numer telefonu:</th><td><?php echo $phoneNumber; ?></td></tr>
<tr><th>Kwota:</th><td><?php echo $ammount; ?></td></tr>

</table>
<?php
endif;
?>

</body>
</html>