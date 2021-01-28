<?php 
    header("Content-type: text/css");
    
    $light_blue = "#00669e";
    $white_news = "#f8f9fa";
    $grey_topbar = "rgb(52,58,64)";
    $light_blue_logo = "rgb(0,112,158)";
    $footer_color = "#222222";
    $navigation_padding = ".5rem";
?>

* {
    font-family: BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, "Noto Sans", sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji", sans-serif;
}

body {
    margin:0;
    padding:0;
}

#container {
    display: flex;
    height: 100%;
    flex-direction: column;
}

h1, h2, h3 {
    font-weight:normal;
}

#top-bar {
    background-color: <?php echo $grey_topbar; ?>;
    height: 6ex;
    display: -webkit-flex;
    display: -ms-flexbox;
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-direction: row;
}

#top-bar a {
    text-decoration: none;
    color: grey;
}
 
#navigation a {
    
    font-size: 0.9rem;
    font-weight: 400;
    line-height: 1.5;
    padding-right: <?php echo $navigation_padding; ?>;
    padding-left: <?php echo $navigation_padding; ?>;
}

#login a {
    padding-right: .9rem;
}

#logo {
    background-color: <?php echo $light_blue_logo; ?>;
    height: 12ex;
}

.container-vertical {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
}

.container-vertical h1 {
    font-size: 3.15rem;
    font-weight: lighter;
}

.container-vertical > * {
    width: 60%;
}

.news-item {
    padding: 3%;
    margin: 1%;
    background-color: <?php echo $white_news; ?>;
    box-sizing: border-box;
}

.news-item h2 {
    font-weight: lighter;
    font-size: 2.25rem;
}

.float-right {
    margin-left: auto;
}

.button {
    text-decoration: none;
    padding: 12px 16px;
    text-align: center;
    display: inline-block;
    font-size: 12px; 
    box-shadow: 3px 3px 8px #888888;
    border-radius: 4px;    
    box-sizing: border-box;
    color: #fff;
}

.button-primary {
    color: #fff;
    background-color: <?php echo $light_blue; ?>;
    border-color: <?php echo $light_blue; ?>;
}

.button-next {
    background-color: #5A6268;
}

.news-item-date {
    float: right;
}

.container-horizontal {
    display: flex;
    flex-wrap: wrap;
    flex-direction: row;
}

.bottom-item {
    flex: 1 1 calc(33.33% - 4%); /* width - margin */
    margin: 2%;
    padding: 0%;
    border: none;
    box-sizing: border-box;
}

#footer {
    background-color: <?php echo $footer_color; ?>;
    color:white;
    height: 50px;
    left: 0;
    bottom: 0;
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
}