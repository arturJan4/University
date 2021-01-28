$(document).ready(function() {
    $("#mainForm").submit(function(event) {
        event.preventDefault() // wylacza POST
        $('label.error-msg').remove();
        $("#form-message").text("");

        handleKeyUp(true);
    });
    // throttle (2000) vs debounce (~500)
    $("#mainForm input").on("keyup change", $.throttle(2000, function(e) {
        handleKeyUp(false);
    }));
});

function handleKeyUp($isSubmitting)  {
    $('label.error-msg').remove();
    $("#form-message").text("");
    
    var data = {}
    $.each($('form input'), function(i, v) {
        if (v.type !== 'submit') {
            data[v.name] = v.value;
        }
        data['submit'] = $("#data-submit").val();
    });
        
    //console.log(data);
    $.post(
        'confirmUser.php',
        data,
        function(result) {
            if(result['success'])
            {
                if($isSubmitting)
                {
                    $("#form-message").text("Sukces"); 
                }
                return true;
            }
            else {
                $('label.error-msg').remove();
                //console.log(result);
                $.each(result, function(key, value) {
                    var message = '<label class="error-msg" for="' + key + '">' + value + '</label>';
                    $('input[name="' + key + '"], select[name="' + key +'"]').after(message);
                });   
            }
        },
        'json'
    ).fail(function(){alert("error sending ajax")});
}