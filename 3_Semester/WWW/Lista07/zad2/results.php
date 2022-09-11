<?php 
    function luhnCheck($number) // for all except unionpay
    {
        $length = strlen($number); // const here
        $checksum = (int)$number[$length-1];
        $even = $length % 2;

        for($i = 0; $i < $length - 1; $i++)
        {
            $digit = (int)$number[$i];
            if($i % 2 == $even) // same parity
            {
                $digit *= 2;
            }
            if($digit > 9) // normalize
            {
                $digit -= 9;
            }
            $checksum += $digit;
        }        

        if (($checksum % 10) == 0) {
            return true;
        } else {
            return false;
        }
    }
?>
<?php
    //$name = $_POST['name'];
    $cardNumber = $_POST['cardNumber'];
    $expDate = $_POST['expDate'];
    $cvcNumber = filter_input(INPUT_POST, 'cvcNumber');
    $name = filter_input(INPUT_POST, 'name');
    $surname = filter_input(INPUT_POST, 'surname');
    $email = filter_input(INPUT_POST, 'email');
    $phoneNumber = filter_input(INPUT_POST, 'phoneNumber');
    $ammount = filter_input(INPUT_POST, 'ammount');
?>
<?php
    for($i = 0; $i < count($cardNumber); ++$i) {
        if(!preg_match('/^\d\d\d\d$/',$cardNumber[$i]))
        {
            $cardNumber_error = "Numer karty kredytowej składa się z cyfr";
        }
    }

    if(!isset($cardNumber_error) && !luhnCheck(join($cardNumber)))
    {
        $cardNumber_error = "Karta kredytowa o nieprawidłowym numerze";
    }

    if(!preg_match('/^(0?[1-9]|1[012])$/',$expDate[0]))
    {
        $expDate_error = "Niepoprawny miesiąc";
    }

    if (!isset($expDate_error) && ("20".$expDate[1] < date('Y') 
        || "20".$expDate[1] == date('Y') && $expDate[0] < date('m'))) {
        $expDate_error = "Karta straciła ważność";
    }

    if(!preg_match('/^\d\d\d$/',$cvcNumber))
    {
        $cvcNumber_error = "Niepoprawny numer CVC";
    }

    if(!preg_match('/^[\p{L} ]+$/u',$name))
    {
        $name_error = "Imię musi składać się z liter";
    }

    if(!preg_match('/^[\p{L} ]+$/u',$surname))
    {
        $surname_error = "Nazwisko musi składać się z liter";
    }

    if(!preg_match('/^(?!(?:(?:\x22?\x5C[\x00-\x7E]\x22?)|(?:\x22?[^\x5C\x22]\x22?)){255,})(?!(?:(?:\x22?\x5C[\x00-\x7E]\x22?)|(?:\x22?[^\x5C\x22]\x22?)){65,}@)(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-\x39\x3D\x3F\x5E-\x7E]+)|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-\x5B\x5D-\x7F]|(?:\x5C[\x00-\x7F]))*\x22))(?:\.(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-\x39\x3D\x3F\x5E-\x7E]+)|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-\x5B\x5D-\x7F]|(?:\x5C[\x00-\x7F]))*\x22)))*@(?:(?:(?!.*[^.]{64,})(?:(?:(?:xn--)?[a-z0-9]+(?:-[a-z0-9]+)*\.){1,126}){1,}(?:(?:[a-z][a-z0-9]*)|(?:(?:xn--)[a-z0-9]+))(?:-[a-z0-9]+)*)|(?:\[(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){7})|(?:(?!(?:.*[a-f0-9][:\]]){7,})(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?)))|(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){5}:)|(?:(?!(?:.*[a-f0-9]:){5,})(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,3})?::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,3}:)?)))?(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9]))(?:\.(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9]))){3}))\]))$/iD',$email))
    {
        $email_error = "Niepoprawny adres email";
    }

    if(!preg_match('/^\d\d\d *\d\d\d *\d\d\d$/',$phoneNumber))
    {
        $phoneNumber_error = "Numer telefonu to 9 cyfr";
    }
    
    if(!(is_numeric($ammount)))
    {
        $ammount_error = "Kwota musi być liczbą";
    }
?>
<?php
    include("index.php");
?>