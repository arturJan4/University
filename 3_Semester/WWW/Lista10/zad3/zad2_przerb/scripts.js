$(document).ready(function() {
    var obj = $("#autocomp");
    var input = $("#movieName");
    suggest(obj, input, 'getMovie.php');
});

function suggest(object, inputField, filepath) {
    var container = $('<div class="auto-container hidden"></div>');
    object.append(container);   // wrap items
    var containerfocus = 0; // current ac-item

    // throttle vs debounce
    inputField.keyup($.throttle(2000,function(e) {
        var input = inputField.val();
        if(input.length <= 0) {
            containerfocus = 0;
            container.css("display", "none");   // dont show dropdown
            return;
        }
        //console.log(containerfocus);
        // arrow controls
        if(e.which == 8) { // backspace
            containerfocus = 0; // reset to first field in dropdown
        }
        else if(e.which == 13) { // enter (select field)
            inputField.val($(".item-ac").eq(containerfocus).text());
            containerfocus = 0;
            container.css("display", 'none');
            return;
        }
        else if(e.which == 38) { // up
            if(containerfocus > 0) {
                $(".item-ac").eq(containerfocus).removeClass('active');
                containerfocus -= 1;
                $(".item-ac").eq(containerfocus).addClass('active');                  
            }
            return;
        }
        else if(e.which == 40) { // down
            if(containerfocus < ($(".item-ac").length - 1)) {
                $(".item-ac").eq(containerfocus).removeClass('active');
                containerfocus += 1;
                $(".item-ac").eq(containerfocus).addClass('active');                  
            } 
            return;
        }
        // ajax request
        $.ajax({
            method: 'POST',
            url: filepath,
            data: {input : input},
            success: function(result) {
                //console.log(result);
                container.empty();
                var responseJSON = JSON.parse(result);
                var isEmpty = responseJSON.length <= 0;
                $.each(responseJSON, function(key, value) {
                    var item = $('<div class="item-ac">' + value + "</div>");
                    
                    $(".item-ac").eq(containerfocus).addClass('active');
                    container.append(item);
                });

                if(!isEmpty) {
                    container.css("display", "block");
                }
                else {
                    container.css("display", "none");
                }
            }
        });
    }));
    
    // clicking on list
    $(document).on('click', function(e) {
        if($(e.target).hasClass("item-ac")){
            inputField.val($(e.target).text());
            containerfocus = 0;
            container.css("display", 'none');
        }
    });   
}