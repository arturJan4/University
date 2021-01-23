$(function() {
    var images = document.getElementsByTagName("img");
    var imagesLength = images.length;
//    var toggled = false; // TODO - change select label
    console.log(images);
    for(i = 0; i < imagesLength; ++i) {
        $(images[i]).data("marked",false);
    }
    
    $("img").click(function() {
        let checked = $(this).data("marked");
        $(this).toggleClass("image-checked");
        $(this).data("marked",!checked);
//        if(!checked) // TODO
//            toggled = true;
    });
    
    $("#select").click(function() {
        checked = false;
        // check if any is checked
        for(i = 0; i < imagesLength; ++i) {
            if($(images[i]).data("marked") == true) {
                checked = true;
                break;
            }
        }
        // if any image is checked, uncheck all
        if(checked) {
            for(i = 0; i < imagesLength; ++i) {
                $(images[i]).removeClass("image-checked");
                $(images[i]).data("marked",false);
            }
        } 
        else {
            for(i = 0; i < imagesLength; ++i) {
                $(images[i]).addClass("image-checked");
                $(images[i]).data("marked",true);
            }
        }
    });
    // saves images id's to log
    $("#save").click(function() {
        let str = "";
        for(i = 0; i < imagesLength; ++i) {
            let curImg = $(images[i]);
            if(curImg.data("marked") == true) {
                str = str + curImg.attr("id") + "\n";
            }
        }
        console.log(str);
        $("#log").text(str);
    });

})