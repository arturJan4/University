<?php 
    //phpinfo(); 
    echo $_SERVER['REQUEST_URI'];       //URL
    echo "</br>";  
    echo $_SERVER['REQUEST_TIME'];      //The IP address of the server under which the current script is executing.
    echo "</br>";  
    echo $_SERVER['SERVER_NAME'];       //The name of the server host under which the current script is executing. If the script is running on a virtual host, this will be the value defined for that virtual host.
    echo "</br>";  
    echo $_SERVER['SERVER_SOFTWARE'];   //Server identification string, given in the headers when responding to requests.
    echo "</br>";  
    echo $_SERVER['REQUEST_METHOD'];    // GET POST HEAD PUT itp.
?>