$( function() {
    var dialog, form,

    postcodeRegex = /^\d{2}-\d{3}$/,
    nameRegex =/^[A-Z]./,
    name = $("#name"),
    surname = $("#surname"),
    city = $("#city"),
    postcode = $("#postcode"),
    birthdate = $("#birthdate"),
    allFields = $( [] ).add(name)
                        .add(surname)
                        .add(city)
                        .add(postcode)
                        .add(birthdate),
    tips = $( ".validateTips" );

    $( "#birthdate" ).datepicker($.datepicker.regional[ "pl" ]);
    
    function updateTips( t ) {
      tips
        .text( t )
        .addClass( "ui-state-highlight" );
      setTimeout(function() {
        tips.removeClass( "ui-state-highlight", 1500 );
      }, 500 );
    }
 
    function checkLength( o, n, min, max ) {
      if ( o.val().length > max || o.val().length < min ) {
        o.addClass( "ui-state-error" );
        updateTips( "Długość " + n + " musi być pomiędzy " +
          min + " a " + max + " znaków." );
        return false;
      } else {
        return true;
      }
    }
 
    function checkRegexp( o, regexp, n ) {
      if ( !( regexp.test( o.val() ) ) ) {
        o.addClass( "ui-state-error" );
        updateTips( n );
        return false;
      } else {
        return true;
      }
    }
 
    function addUser() {
      var valid = true;
      allFields.removeClass( "ui-state-error" );
      
      valid = valid && checkLength(city, "nazwy miasta", 2, 64 );
      
      valid = valid && checkRegexp(name,nameRegex,"Imię powinno zaczynać się dużą literą");
      valid = valid && checkRegexp(surname,nameRegex,"Nazwisko powinno zaczynać się dużą literą");
      valid = valid && checkRegexp(postcode,postcodeRegex,"Adres pocztowy musi być w formacie ABC-DE");

      if ( valid ) {
        $( "#users tbody" ).append( "<tr>" +
          "<td>" + name.val() + "</td>" +
          "<td>" + surname.val() + "</td>" +
          "<td>" + city.val() + "</td>" +
          "<td>" + postcode.val() + "</td>" +
          "<td>" + birthdate.val() + "</td>" +
          "<td><button type='button' class='removebutton' title='remove'>Usuń</button></td>" +
        "</tr>" );
        dialog.dialog( "close" );
      }
      return valid;
    }
 
    dialog = $( "#dialog-form" ).dialog({
      autoOpen: false,
      height: 600,
      width: 400,
      modal: true,
      buttons: {
        "Dodaj użytkownika": addUser,
        "Anuluj": function() {
          dialog.dialog( "close" );
        }
      },
      "Zamknij": function() {
        form[ 0 ].reset();
        allFields.removeClass( "ui-state-error" );
      }
    });
 
    form = dialog.find( "form" ).on( "submit", function( event ) {
      event.preventDefault();
      addUser();
    });
 
    $( "#create-user" ).button().on( "click", function() {
      dialog.dialog( "open" );
    });

    $( "#dialog-confirm-remove" ).dialog({
      resizable: false,
      height: "auto",
      width: 400,
      modal: true,
      autoOpen: false,
      buttons: {
        "Tak": function() {
          $(".selected-remove").remove();
          $( this ).dialog( "close" );
        },
        "Nie": function() {
          $(".selected-remove").removeClass("selected-remove");
          $( this ).dialog( "close" );
        }
      }
    });
    
    $(document).on("click", ".removebutton", (function() {
      $(this).parents("tr").addClass("selected-remove")
      $("#dialog-confirm-remove").dialog("open");
    }));
});