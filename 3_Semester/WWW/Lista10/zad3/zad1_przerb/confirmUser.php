<?php
    header( "Cache-Control: max-age=-1" );

    function isCorrectPassword($password) {
        $uppercase = preg_match('/[A-Z]/', $password);
        $lowercase = preg_match('/[a-z]/', $password);
        $number    = preg_match('/[0-9]/', $password);
        $length = strlen($password) >= 8;
        return $uppercase && $lowercase && $number && $length;
    }
    function isCorrectDate($date) {
        return preg_match('/^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[012])-(19|20)\d\d$/', $date);
    }

    session_start();
    if (isset($_POST['submit'])) {
        $login = (isset($_POST["login"])) ? htmlspecialchars($_POST["login"]) : "";
        $password = (isset($_POST["password"])) ? htmlspecialchars($_POST["password"]) : "";
        $password_repeat = (isset($_POST["password_repeat"])) ? htmlspecialchars($_POST["password_repeat"]) : "";
        $birthdate = (isset($_POST["birthdate"])) ? htmlspecialchars($_POST["birthdate"]) : "";       
        
        $_SESSION['errors']['success'] = false;
        if (empty($login)) {
            $_SESSION['errors']['login'] = 'Wpisz login';
        }
        else if(strlen($login) < 8) {
            $_SESSION['errors']['login'] = 'Login musi zawierać przynajmniej 8 znaków';
        }

        if (empty($password)) {
            $_SESSION['errors']['password'] = 'Wpisz hasło';
        }
        else if(!isCorrectPassword($password)) {
            $_SESSION['errors']['password'] = 'Hasło powinno zawierać przynajmniej 8 znaków, duża literę i cyfrę';
        }

        if (empty($password_repeat)) {
            $_SESSION['errors']['password_repeat'] = 'Powtórz hasło';
        }
        else if($password_repeat != $password) {
            $_SESSION['errors']['password_repeat'] = 'Podane hasła się różnią';
        }

        if (empty($birthdate)) {
            $_SESSION['errors']['birthdate'] = 'Wpisz datę urodzenia';
        }
        else if(!isCorrectDate($birthdate)) {
            $_SESSION['errors']['birthdate'] = 'Niepoprawny format daty urodzenia (oczekiwany DD-MM-YYYY)';
        }

        if(count($_SESSION['errors']) == 1) {
            $_SESSION['errors']['success'] = true;
            // do sth with the data
        }
            
        echo json_encode($_SESSION['errors']);  
        session_unset(); // frees variables
        exit;
    }
?>